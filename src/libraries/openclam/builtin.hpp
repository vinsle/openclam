//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_BUILTIN_HPP_INCLUDED
#define OPENCLAM_BUILTIN_HPP_INCLUDED

#include <boost/noncopyable.hpp>

namespace openclam
{

class builtin : private boost::noncopyable
{
public:
             builtin() {}
    virtual ~builtin() {}
protected:
    unsigned int get_global_id( unsigned int ){ return 0; }
};

}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
