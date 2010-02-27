//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/cl.hpp"
#include <memory>

BOOST_AUTO_TEST_CASE( simple_kernel_instanciation )
{
    const std::string expected =
        "__kernel void VectorAdd( __global const float* a, __global const float* b, __global float* c, unsigned int size ) "
        "{ "
        "const unsigned int iGID = get_global_id( 0 ); "
        "if( iGID >= size ) "
        "return; "
        "c[ iGID ] = a[ iGID ] + b[ iGID ]; "
        "}";
    const std::string actual = KERNEL( VectorAdd,
        __kernel void VectorAdd( __global const float* a, __global const float* b, __global float* c, unsigned int size )
        {
            const unsigned int iGID = get_global_id( 0 );
            if( iGID >= size )
                return;
            c[ iGID ] = a[ iGID ] + b[ iGID ];
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}
