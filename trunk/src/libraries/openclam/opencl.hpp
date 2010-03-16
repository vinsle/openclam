//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_OPENCL_HPP_INCLUDED
#define OPENCLAM_OPENCL_HPP_INCLUDED

#include "iopencl.hpp"

namespace openclam
{

class opencl : public iopencl
{
public:
             opencl() {}
    virtual ~opencl() {}

    virtual cl_context clCreateContextFromType( const cl_context_properties*  properties,
                                                cl_device_type device_type,
                                                void ( *pfn_notify )( const char*, const void*, size_t, void * ),
                                                void* user_data,
                                                cl_int* errcode_ret ) const
    {
        return ::clCreateContextFromType( properties, device_type, pfn_notify, user_data, errcode_ret );
    }

    virtual cl_int clGetContextInfo( cl_context context,
                                     cl_context_info param_name, 
                                     size_t param_value_size, 
                                     void* param_value, 
                                     size_t* param_value_size_ret ) const
    {
        return ::clGetContextInfo( context, param_name, param_value_size, param_value, param_value_size_ret );
    }

    virtual cl_command_queue clCreateCommandQueue( cl_context context,
                                                   cl_device_id device, 
                                                   cl_command_queue_properties properties,
                                                   cl_int* errcode_ret ) const
    {
        return ::clCreateCommandQueue( context, device, properties, errcode_ret );
    }

    virtual cl_int clReleaseCommandQueue( cl_command_queue command_queue ) const
    {
        return ::clReleaseCommandQueue( command_queue );
    }

    virtual cl_int clReleaseContext( cl_context context ) const
    {
        return ::clReleaseContext( context );
    }

    virtual cl_program clCreateProgramWithSource( cl_context context,
                                                  cl_uint count,
                                                  const char** strings,
                                                  const size_t* lengths,
                                                  cl_int* errcode_ret ) const
    {
        return ::clCreateProgramWithSource( context, count, strings, lengths, errcode_ret );
    }

    virtual cl_mem clCreateBuffer( cl_context context,
                                   cl_mem_flags flags,
                                   size_t size,
                                   void* host_ptr,
                                   cl_int* errcode_ret ) const
    {
        return ::clCreateBuffer( context, flags, size, host_ptr, errcode_ret );
    }

    virtual cl_int clSetKernelArg( cl_kernel clkernel,
                                   cl_uint arg_index,
                                   size_t arg_size,
                                   const void* arg_value ) const
    {
        return ::clSetKernelArg( clkernel, arg_index, arg_size, arg_value );
    }

    virtual cl_int clEnqueueWriteBuffer( cl_command_queue command_queue, 
                                         cl_mem buffer, 
                                         cl_bool blocking_write, 
                                         size_t offset, 
                                         size_t cb, 
                                         const void* ptr, 
                                         cl_uint num_events_in_wait_list, 
                                         const cl_event* event_wait_list, 
                                         cl_event* event ) const
    {
        return ::clEnqueueWriteBuffer( command_queue, buffer, blocking_write, offset, cb, ptr, num_events_in_wait_list, event_wait_list, event );
    }

    virtual cl_int clEnqueueNDRangeKernel( cl_command_queue command_queue,
                                           cl_kernel clkernel,
                                           cl_uint work_dim,
                                           const size_t* global_work_offset,
                                           const size_t* global_work_size,
                                           const size_t* local_work_size,
                                           cl_uint num_events_in_wait_list,
                                           const cl_event* event_wait_list,
                                           cl_event* event ) const
    {
        return ::clEnqueueNDRangeKernel( command_queue, clkernel, work_dim, global_work_offset, global_work_size,
                                         local_work_size, num_events_in_wait_list, event_wait_list, event );
    }

    virtual cl_int clEnqueueReadBuffer( cl_command_queue command_queue,
                                        cl_mem buffer,
                                        cl_bool blocking_read,
                                        size_t offset,
                                        size_t cb, 
                                        void* ptr,
                                        cl_uint num_events_in_wait_list,
                                        const cl_event* event_wait_list,
                                        cl_event* event ) const
    {
        return ::clEnqueueReadBuffer( command_queue, buffer, blocking_read, offset, cb, ptr, num_events_in_wait_list, event_wait_list, event );
    }

    virtual cl_int clReleaseMemObject( cl_mem memobj ) const
    {
        return ::clReleaseMemObject( memobj );
    }

};

}

#endif // #ifndef OPENCLAM_OPENCL_HPP_INCLUDED
