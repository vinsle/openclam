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
    const float added = 3.f;

    const char * addKernel = KERNEL(
        __kernel void VectorAdd( __global const float* a, __global const float* b, __global float* c, unsigned int size )
    {
        const unsigned int iGID = get_global_id( 0 );
        if( iGID >= size )
            return;
        c[ iGID ] = a[ iGID ] + b[ iGID ];
    } );

    unsigned int RoundUp( unsigned int group_size, unsigned int global_size ) 
    {
        int r = global_size % group_size;
        if( r == 0 )
            return global_size;
        return global_size + group_size - r;
    }
}

BOOST_AUTO_TEST_CASE( setting_up_openclam_framework )
{
    // set and log Global and Local work size dimensions
    const unsigned int size = 100u;
    const unsigned int localSize = 256;
    const unsigned int globalSize = RoundUp( localSize, size );  // rounded up to the nearest multiple of the LocalWorkSize

    std::auto_ptr< float >srcA( new float[ globalSize ] );
    std::auto_ptr< float >srcB( new float[ globalSize ] );
    std::auto_ptr< float >dst( new float[ globalSize ] );

    // Allocate and initialize host arrays 
    for( unsigned int i = 0; i < size; ++i )
    {
        srcA.get()[ i ] = static_cast< float >( i );
        srcB.get()[ i ] = added;
    }

    // Create the OpenCL context on a GPU device
    cl_int err1, err2;
    cl_context cxGPUContext = clCreateContextFromType( 0, CL_DEVICE_TYPE_GPU, NULL, NULL, &err1 );

    // Get the list of GPU devices associated with context
    unsigned int szParmDataBytes;
    err1 = clGetContextInfo( cxGPUContext, CL_CONTEXT_DEVICES, 0, NULL, &szParmDataBytes );
    std::auto_ptr< cl_device_id > cdDevices( new cl_device_id[ szParmDataBytes ] );
    err1 |= clGetContextInfo( cxGPUContext, CL_CONTEXT_DEVICES, szParmDataBytes, cdDevices.get(), NULL );

    // Create a command-queue
    cl_command_queue cqCommandQue = clCreateCommandQueue( cxGPUContext, cdDevices.get()[ 0 ], 0, &err1 );

    // Allocate the OpenCL buffer memory objects for source and result on the device GMEM
    cl_mem cmDevSrcA = clCreateBuffer( cxGPUContext, CL_MEM_READ_ONLY, sizeof(cl_float) * globalSize, NULL, &err1 );
    cl_mem cmDevSrcB = clCreateBuffer( cxGPUContext, CL_MEM_READ_ONLY, sizeof(cl_float) * globalSize, NULL, &err2 );
    err1 |= err2;
    cl_mem cmDevDst = clCreateBuffer( cxGPUContext, CL_MEM_WRITE_ONLY, sizeof(cl_float) * globalSize, NULL, &err2 );
    err1 |= err2;

    // Create the program
    unsigned int szKernelLength;
    szKernelLength = strlen( addKernel );
    cl_program cpProgram = clCreateProgramWithSource( cxGPUContext, 1, (const char **)&addKernel, &szKernelLength, &err1 );

    // Build the program
    err1 = clBuildProgram( cpProgram, 0, NULL, NULL, NULL, NULL );

    // Create the kernel
    cl_kernel ckKernel = clCreateKernel( cpProgram, "VectorAdd", &err1 );

    // Set the Argument values
    err1 = clSetKernelArg( ckKernel, 0, sizeof(cl_mem), (void*)&cmDevSrcA );
    err1 |= clSetKernelArg( ckKernel, 1, sizeof(cl_mem), (void*)&cmDevSrcB );
    err1 |= clSetKernelArg( ckKernel, 2, sizeof(cl_mem), (void*)&cmDevDst );
    err1 |= clSetKernelArg( ckKernel, 3, sizeof(cl_int), (void*)&size );

    // --------------------------------------------------------
    // Start Core sequence... copy input data to GPU, compute, copy results back

    // Asynchronous write of data to GPU device
    err1 = clEnqueueWriteBuffer( cqCommandQue, cmDevSrcA, CL_FALSE, 0, sizeof(cl_float) * globalSize, srcA.get(), 0, NULL, NULL );
    err1 |= clEnqueueWriteBuffer( cqCommandQue, cmDevSrcB, CL_FALSE, 0, sizeof(cl_float) * globalSize, srcB.get(), 0, NULL, NULL );

    // Launch kernel
    err1 = clEnqueueNDRangeKernel( cqCommandQue, ckKernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL );

    // Synchronous/blocking read of results, and check accumulated errors
    err1 = clEnqueueReadBuffer( cqCommandQue, cmDevDst, CL_TRUE, 0, sizeof(cl_float) * globalSize, dst.get(), 0, NULL, NULL );
    //--------------------------------------------------------

    // Compute and compare results for golden-host and report errors and pass/fail
    for( unsigned int i = 0; i < size; ++i )
        BOOST_CHECK_EQUAL( srcA.get()[ i ] + added, dst.get()[ i ] );
}
