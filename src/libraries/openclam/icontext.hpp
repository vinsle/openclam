//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_ICONTEXT_HPP_INCLUDED
#define OPENCLAM_ICONTEXT_HPP_INCLUDED

#include "ikernel_proxy.hpp"
#include <memory>
#include <string>
#include <boost/noncopyable.hpp>

namespace openclam
{
class icontext : private boost::noncopyable
{
public:
    enum device_type
    {
        default_    = CL_DEVICE_TYPE_DEFAULT,
        cpu         = CL_DEVICE_TYPE_CPU,
        gpu         = CL_DEVICE_TYPE_GPU,
        accelerator = CL_DEVICE_TYPE_ACCELERATOR,
        all         = CL_DEVICE_TYPE_ALL
    };

             icontext() {}
    virtual ~icontext() {}

    virtual std::auto_ptr< openclam::ikernel_proxy > create( const std::string& name, const std::string& sources ) const = 0;
    virtual void execute( void* data, size_t size, const openclam::ikernel_proxy& k ) const = 0;
};
}

#endif // #ifndef OPENCLAM_ICONTEXT_HPP_INCLUDED
