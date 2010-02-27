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

enum DeviceType
{
    Default     = CL_DEVICE_TYPE_DEFAULT,
    Cpu         = CL_DEVICE_TYPE_CPU,
    Gpu         = CL_DEVICE_TYPE_GPU,
    Accelerator = CL_DEVICE_TYPE_ACCELERATOR,
    All         = CL_DEVICE_TYPE_ALL
};

class context : private boost::noncopyable
{
public:
    explicit context( DeviceType type = Default )
        : type_( type )
    {
        ERROR_HANDLER( clContext_ = clCreateContextFromType( 0, type_, NULL, NULL, &error ); )
    }
    virtual ~context() {}

private:
    const DeviceType type_;
    cl_context clContext_;
};

}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
