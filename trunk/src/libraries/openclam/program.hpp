//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_PROGRAM_HPP_INCLUDED
#define OPENCLAM_PROGRAM_HPP_INCLUDED

#include <memory>
#include <string>
#include <boost/noncopyable.hpp>

namespace openclam
{

class program : private boost::noncopyable
{
public:
    explicit program( cl_program program )
        : program_( program )
    {
        ERROR_HANDLER( ERROR = clBuildProgram( program_, 0, NULL, NULL, NULL, NULL ) );
    }
    virtual ~program()
    {
        clReleaseProgram( program_ ); // $$$$ 28-02-2010 SILVIN: check error code?
    }

    cl_kernel create( const std::string& name ) const
    {       
        cl_kernel result;
        ERROR_HANDLER( result = clCreateKernel( program_, name.c_str(), &ERROR ) );
        return result;
    }
private:
    const cl_program program_;
};

}

#endif // #ifndef OPENCLAM_PROGRAM_HPP_INCLUDED
