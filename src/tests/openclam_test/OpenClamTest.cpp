//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "Test.h"
#include "openclam/cl.hpp"
#include <memory>

namespace
{
    const unsigned int iNumElements = 100u;
    const float added = 3.f;

    const char * addKernel = KERNEL(
        __kernel void VectorAdd( __global const float* a, __global const float* b, __global float* c, int iNumElements )
    {
        const int iGID = get_global_id( 0 );
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
}

BOOST_AUTO_TEST_CASE( test3 )
{
    // set and log Global and Local work size dimensions
    const size_t szLocalWorkSize = 256;
    const size_t szGlobalWorkSize = shrRoundUp( szLocalWorkSize, iNumElements );  // rounded up to the nearest multiple of the LocalWorkSize

    std::auto_ptr< float >srcA( new float[ szGlobalWorkSize ] );
    std::auto_ptr< float >srcB( new float[ szGlobalWorkSize ] );
    std::auto_ptr< float >dst( new float[ szGlobalWorkSize ] );

    cl_context cxGPUContext;
    cl_command_queue cqCommandQue;
    cl_program cpProgram;
    cl_kernel ckKernel;
    cl_mem cmDevSrcA;
    cl_mem cmDevSrcB;
    cl_mem cmDevDst;
    size_t szParmDataBytes;
    size_t szKernelLength;
    cl_int ciErr1, ciErr2;

    // Allocate and initialize host arrays 
    for( unsigned int i = 0; i < iNumElements; ++i )
        srcA.get()[ i ] = static_cast< float >( i );
    for( unsigned int i = 0; i < iNumElements; ++i )
        srcB.get()[ i ] = added;

    // Create the OpenCL context on a GPU device
    cxGPUContext = clCreateContextFromType( 0, CL_DEVICE_TYPE_GPU, NULL, NULL, &ciErr1 );

    // Get the list of GPU devices associated with context
    ciErr1 = clGetContextInfo( cxGPUContext, CL_CONTEXT_DEVICES, 0, NULL, &szParmDataBytes );
    std::auto_ptr< cl_device_id > cdDevices( new cl_device_id[ szParmDataBytes ] );
    ciErr1 |= clGetContextInfo( cxGPUContext, CL_CONTEXT_DEVICES, szParmDataBytes, cdDevices.get(), NULL );

    // Create a command-queue
    cqCommandQue = clCreateCommandQueue( cxGPUContext, cdDevices.get()[ 0 ], 0, &ciErr1 );

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
    ciErr1 = clEnqueueWriteBuffer( cqCommandQue, cmDevSrcA, CL_FALSE, 0, sizeof(cl_float) * szGlobalWorkSize, srcA.get(), 0, NULL, NULL );
    ciErr1 |= clEnqueueWriteBuffer( cqCommandQue, cmDevSrcB, CL_FALSE, 0, sizeof(cl_float) * szGlobalWorkSize, srcB.get(), 0, NULL, NULL );

    // Launch kernel
    ciErr1 = clEnqueueNDRangeKernel( cqCommandQue, ckKernel, 1, NULL, &szGlobalWorkSize, &szLocalWorkSize, 0, NULL, NULL );

    // Synchronous/blocking read of results, and check accumulated errors
    ciErr1 = clEnqueueReadBuffer( cqCommandQue, cmDevDst, CL_TRUE, 0, sizeof(cl_float) * szGlobalWorkSize, dst.get(), 0, NULL, NULL );
    //--------------------------------------------------------

    // Compute and compare results for golden-host and report errors and pass/fail
    for( unsigned int i = 0; i < iNumElements; ++i )
        BOOST_CHECK_EQUAL( srcA.get()[ i ] + added, dst.get()[ i ] );
}
