// *****************************************************************************
//
// This file is part of a MASA library or program.
// Refer to the included end-user license agreement for restrictions.
//
// Copyright (c) 2010 Mathématiques Appliquées SA (MASA)
//
// *****************************************************************************

#define __CL_ENABLE_EXCEPTIONS
#pragma warning( push )
#pragma warning( disable: 4100 4245 4290 4510 4512 4610 )
#include <CL/cl.hpp>
#include "openclam/cl.hpp"
#include <math.h>
#pragma warning( pop )
#include <boost/test/auto_unit_test.hpp>
#define BOOST_LIB_NAME boost_unit_test_framework
#include <boost/config/auto_link.hpp>

namespace
{
    std::string data_directory;

    void set_data_directory( int argc, char* argv[] )
    {
        while( argc-- )
        {
            const std::string argument = argv[argc];
            const std::string::size_type n = argument.find( '=' );
            if( n != std::string::npos && argument.substr( 0, n ) == "--data_directory" )
                data_directory = argument.substr( n+1 );
        }
    }
}

::boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    set_data_directory( argc, argv );
    return 0;
}

std::string BOOST_RESOLVE( const std::string& filename )
{
    if( data_directory.empty() )
        return filename;
    return data_directory + '/' + filename;
}

namespace
{
    void *srcA, *srcB, *dst;
    void* Golden;

    cl_context cxGPUContext;
    cl_command_queue cqCommandQue;
    cl_device_id* cdDevices;
    cl_program cpProgram;
    cl_kernel ckKernel;
    cl_mem cmDevSrcA;
    cl_mem cmDevSrcB;
    cl_mem cmDevDst;
    size_t szGlobalWorkSize;
    size_t szLocalWorkSize;
    size_t szParmDataBytes;
    size_t szKernelLength;
    cl_int ciErr1, ciErr2;
    char* cPathAndName = NULL;
    char* cSourceCL = NULL;
    int iNumElements = 11444777;

    KERNEL( const char * addKernel,
    void VectorAdd( GLOBAL const float* a, GLOBAL const float* b, GLOBAL float* c, int iNumElements )
    {
        int iGID = get_global_id( 0 );
        if( iGID >= iNumElements )
            return;
        c[ iGID ] = a[ iGID ] + b[ iGID ];
    } );

    size_t shrRoundUp( int group_size, int global_size ) 
    {
        int r = global_size % group_size;
        if( r == 0 )
            return global_size;
        return global_size + group_size - r;
    }
    void shrFillArray( float* pfData, int iSize )
    {
        int i;
        const float fScale = 1.0f / (float)RAND_MAX;
        for( i = 0; i < iSize; ++i ) 
            pfData[i] = fScale * rand();
    }
    int shrDiffArray( const float* pfResult1, const float* pfResult2, int iNumElements )
    {
        int iErrorCount = 0, i;
        for( i = 0; i < iNumElements; i++ )
            if( fabs( pfResult2[ i ] - pfResult1[ i ] ) > 1e-5 ) 
                iErrorCount++;
        return iErrorCount;
    }
    // "Golden" Host processing vector addition function for comparison purposes
    // *********************************************************************
    void VectorAddHost( const float* pfData1, const float* pfData2, float* pfResult, int iNumElements )
    {
        int i;
        for ( i = 0; i < iNumElements; i++ ) 
            pfResult[ i ] = pfData1[ i ] + pfData2[ i ]; 
    }

}

BOOST_AUTO_TEST_CASE( test3 )
{
    // set and log Global and Local work size dimensions
    szLocalWorkSize = 256;
    szGlobalWorkSize = shrRoundUp( (int)szLocalWorkSize, iNumElements );  // rounded up to the nearest multiple of the LocalWorkSize

    // Allocate and initialize host arrays 
    srcA = (void *)malloc( sizeof( cl_float ) * szGlobalWorkSize );
    srcB = (void *)malloc( sizeof( cl_float ) * szGlobalWorkSize );
    dst = (void *)malloc( sizeof(cl_float ) * szGlobalWorkSize );
    Golden = (void *)malloc( sizeof(cl_float) * iNumElements );
    shrFillArray( (float*)srcA, iNumElements );
    shrFillArray( (float*)srcB, iNumElements );

    // Create the OpenCL context on a GPU device
    cxGPUContext = clCreateContextFromType( 0, CL_DEVICE_TYPE_GPU, NULL, NULL, &ciErr1 );

    // Get the list of GPU devices associated with context
    ciErr1 = clGetContextInfo( cxGPUContext, CL_CONTEXT_DEVICES, 0, NULL, &szParmDataBytes );
    cdDevices = ( cl_device_id* )malloc( szParmDataBytes );
    ciErr1 |= clGetContextInfo( cxGPUContext, CL_CONTEXT_DEVICES, szParmDataBytes, cdDevices, NULL );

    // Create a command-queue
    cqCommandQue = clCreateCommandQueue( cxGPUContext, cdDevices[ 0 ], 0, &ciErr1 );

    // Allocate the OpenCL buffer memory objects for source and result on the device GMEM
    cmDevSrcA = clCreateBuffer( cxGPUContext, CL_MEM_READ_ONLY, sizeof(cl_float) * szGlobalWorkSize, NULL, &ciErr1 );
    cmDevSrcB = clCreateBuffer( cxGPUContext, CL_MEM_READ_ONLY, sizeof(cl_float) * szGlobalWorkSize, NULL, &ciErr2 );
    ciErr1 |= ciErr2;
    cmDevDst = clCreateBuffer( cxGPUContext, CL_MEM_WRITE_ONLY, sizeof(cl_float) * szGlobalWorkSize, NULL, &ciErr2 );
    ciErr1 |= ciErr2;

    // Create the program
    szKernelLength = strlen( addKernel );
    cpProgram = clCreateProgramWithSource( cxGPUContext, 1, (const char **)&addKernel, &szKernelLength, &ciErr1 );

    // Build the program
    ciErr1 = clBuildProgram( cpProgram, 0, NULL, NULL, NULL, NULL );

    // Create the kernel
    ckKernel = clCreateKernel( cpProgram, "VectorAdd", &ciErr1 );

    // Set the Argument values
    ciErr1 = clSetKernelArg( ckKernel, 0, sizeof(cl_mem), (void*)&cmDevSrcA );
    ciErr1 |= clSetKernelArg( ckKernel, 1, sizeof(cl_mem), (void*)&cmDevSrcB );
    ciErr1 |= clSetKernelArg( ckKernel, 2, sizeof(cl_mem), (void*)&cmDevDst );
    ciErr1 |= clSetKernelArg( ckKernel, 3, sizeof(cl_int), (void*)&iNumElements );

    // --------------------------------------------------------
    // Start Core sequence... copy input data to GPU, compute, copy results back

    // Asynchronous write of data to GPU device
    ciErr1 = clEnqueueWriteBuffer( cqCommandQue, cmDevSrcA, CL_FALSE, 0, sizeof(cl_float) * szGlobalWorkSize, srcA, 0, NULL, NULL );
    ciErr1 |= clEnqueueWriteBuffer( cqCommandQue, cmDevSrcB, CL_FALSE, 0, sizeof(cl_float) * szGlobalWorkSize, srcB, 0, NULL, NULL );

    // Launch kernel
    ciErr1 = clEnqueueNDRangeKernel( cqCommandQue, ckKernel, 1, NULL, &szGlobalWorkSize, &szLocalWorkSize, 0, NULL, NULL );

    // Synchronous/blocking read of results, and check accumulated errors
    ciErr1 = clEnqueueReadBuffer( cqCommandQue, cmDevDst, CL_TRUE, 0, sizeof(cl_float) * szGlobalWorkSize, dst, 0, NULL, NULL );
    //--------------------------------------------------------

    // Compute and compare results for golden-host and report errors and pass/fail
    VectorAddHost( (const float*)srcA, (const float*)srcB, (float*)Golden, iNumElements );
    BOOST_CHECK_EQUAL( 0, shrDiffArray(( const float*)dst, (const float*)Golden, iNumElements ) );
}
