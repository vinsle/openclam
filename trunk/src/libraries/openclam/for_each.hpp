//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_FOR_EACH_HPP_INCLUDED
#define OPENCLAM_FOR_EACH_HPP_INCLUDED

#include "kernel.hpp"
#include <memory>

namespace openclam
{
    template< class InputIterator, class Kernel >
    void for_each( InputIterator first, InputIterator last, Kernel& k )
    {
        std::vector< InputIterator::value_type* > data;
        for( ; first != last; ++first )
            data.push_back( &*first );
        k( data[ 0 ], data.size() );
    }
}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
