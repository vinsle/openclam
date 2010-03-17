//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_PROGRAM_HPP_INCLUDED
#define OPENCLAM_PROGRAM_HPP_INCLUDED

#include "error.hpp"
#include "iprogram.hpp"
#include "iopencl.hpp"
#include "kernel_proxy.hpp"
#include <memory>
#include <string>

namespace openclam
{

class program : public openclam::iprogram
{
public:
    program( const openclam::iopencl& wrapper, cl_program program )
        : wrapper_( wrapper )
        , program_( program )
    {
        ERROR_HANDLER( ERROR = wrapper_.clBuildProgram( program_, 0, NULL, NULL, NULL, NULL ) );
    }
    virtual ~program()
    {
        wrapper_.clReleaseProgram( program_ ); // $$$$ 28-02-2010 SILVIN: check error code?
    }

    virtual std::auto_ptr< openclam::kernel_proxy > create( const std::string& name ) const
    {       
        cl_kernel result;
        ERROR_HANDLER( result = wrapper_.clCreateKernel( program_, name.c_str(), &ERROR ) );
        return std::auto_ptr< openclam::kernel_proxy >( new openclam::kernel_proxy( wrapper_, result ) );
    }
private:
    const openclam::iopencl& wrapper_;
    const cl_program program_;
};

}

#endif // #ifndef OPENCLAM_PROGRAM_HPP_INCLUDED
