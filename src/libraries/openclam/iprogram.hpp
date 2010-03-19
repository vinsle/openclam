//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_IPROGRAM_HPP_INCLUDED
#define OPENCLAM_IPROGRAM_HPP_INCLUDED

#include "ikernel_proxy.hpp"
#include <memory>
#include <string>
#include <boost/noncopyable.hpp>

namespace openclam
{

class iprogram : private boost::noncopyable
{
public:
             iprogram() {}
    virtual ~iprogram() {}

    virtual std::auto_ptr< openclam::ikernel_proxy > create( const std::string& name ) const = 0;
};

}

#endif // #ifndef OPENCLAM_IPROGRAM_HPP_INCLUDED
