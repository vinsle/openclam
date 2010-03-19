//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_IKERNEL_PROXY_HPP_INCLUDED
#define OPENCLAM_IKERNEL_PROXY_HPP_INCLUDED

#include <cl/cl.h>
#include <boost/noncopyable.hpp>

namespace openclam
{

class ikernel_proxy : private boost::noncopyable
{
public:
             ikernel_proxy() {}
    virtual ~ikernel_proxy() {}

    virtual void execute( void* data, size_t size, cl_context context, cl_command_queue queue ) const = 0;
};

}

#endif // #ifndef OPENCLAM_IKERNEL_PROXY_HPP_INCLUDED
