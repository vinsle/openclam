//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_IOPENCL_HPP_INCLUDED
#define OPENCLAM_IOPENCL_HPP_INCLUDED

#include <CL/cl.h>
#include <boost/noncopyable.hpp>

namespace openclam
{

class iopencl : private boost::noncopyable
{
public:
             iopencl() {}
    virtual ~iopencl() {}

    virtual cl_context clCreateContextFromType( const cl_context_properties* properties,
                                                cl_device_type device_type,
                                                void ( *pfn_notify )( const char*, const void*, size_t, void* ),
                                                void* user_data,
                                                cl_int* errcode_ret ) const = 0;

    virtual cl_int clGetContextInfo( cl_context context,
                                     cl_context_info param_name,
                                     size_t param_value_size,
                                     void* param_value,
                                     size_t* param_value_size_ret ) const = 0;

    virtual cl_command_queue clCreateCommandQueue( cl_context context,
                                                   cl_device_id device, 
                                                   cl_command_queue_properties properties,
                                                   cl_int* errcode_ret ) const = 0;

    virtual cl_int clReleaseCommandQueue( cl_command_queue command_queue ) const = 0;

    virtual cl_int clReleaseContext( cl_context context ) const = 0;

    virtual cl_program clCreateProgramWithSource( cl_context context,
                                                  cl_uint count,
                                                  const char** strings,
                                                  const size_t* lengths,
                                                  cl_int* errcode_ret ) const = 0;

    virtual cl_mem clCreateBuffer( cl_context context,
                                   cl_mem_flags flags,
                                   size_t size,
                                   void* host_ptr,
                                   cl_int* errcode_ret ) const = 0;

    virtual cl_int clSetKernelArg( cl_kernel kernel,
                                   cl_uint arg_index,
                                   size_t arg_size,
                                   const void* arg_value ) const = 0;

    virtual cl_int clEnqueueWriteBuffer( cl_command_queue command_queue, 
                                         cl_mem buffer, 
                                         cl_bool blocking_write, 
                                         size_t offset, 
                                         size_t cb, 
                                         const void* ptr, 
                                         cl_uint num_events_in_wait_list, 
                                         const cl_event* event_wait_list, 
                                         cl_event* event ) const = 0;

    virtual cl_int clEnqueueNDRangeKernel( cl_command_queue command_queue,
                                           cl_kernel kernel,
                                           cl_uint work_dim,
                                           const size_t* global_work_offset,
                                           const size_t* global_work_size,
                                           const size_t* local_work_size,
                                           cl_uint num_events_in_wait_list,
                                           const cl_event* event_wait_list,
                                           cl_event* event ) const = 0;

    virtual cl_int clEnqueueReadBuffer( cl_command_queue command_queue,
                                        cl_mem buffer,
                                        cl_bool blocking_read,
                                        size_t offset,
                                        size_t cb, 
                                        void* ptr,
                                        cl_uint num_events_in_wait_list,
                                        const cl_event* event_wait_list,
                                        cl_event* event ) const = 0;

    virtual cl_int clReleaseMemObject( cl_mem memobj ) const = 0;
};

}

#endif // #ifndef OPENCLAM_IOPENCL_HPP_INCLUDED
