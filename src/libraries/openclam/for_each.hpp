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
#include <iostream>

namespace openclam
{
    template< typename T, class InputIterator, class Kernel >
    void for_each( InputIterator first, InputIterator last, Kernel& k )
    {
        const unsigned int size = std::distance( first, last ); // $$$$ 2010-03-09 SILVIN: externalize these functions into openclam::buffer or vector object
        T* data = new T[ size ];
        InputIterator it = first;
        for( unsigned int i = 0; it != last; ++it, ++i )
            data[ i ] = *it;
        k( data, size );
        for( unsigned int i = 0; first != last; ++first, ++i )
            std::swap( *first, data[ i ] );
        delete[]( data );
    }
}

#endif // #ifndef OPENCLAM_CONTEXT_HPP_INCLUDED
