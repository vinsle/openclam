//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
#define OPENCLAM_CONTEXT_HPP_INCLUDED

#include <boost/noncopyable.hpp>

namespace openclam
{

class context : private boost::noncopyable
{
public:
    enum device_type
    {
        default     = CL_DEVICE_TYPE_DEFAULT,
        cpu         = CL_DEVICE_TYPE_CPU,
        gpu         = CL_DEVICE_TYPE_GPU,
        accelerator = CL_DEVICE_TYPE_ACCELERATOR,
        all         = CL_DEVICE_TYPE_ALL
    };

    explicit context( device_type type = default )
        : type_( type )
    {
        ERROR_HANDLER( clContext_ = clCreateContextFromType( 0, type_, NULL, NULL, &error ); )
    }
    virtual ~context() {}

private:
    const device_type type_;
    cl_context clContext_;
};

}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
