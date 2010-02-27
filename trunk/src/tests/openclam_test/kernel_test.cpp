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
        "__kernel void MyKernel( __global const float* a, global unsigned int size ) "
        "{ "
        "const unsigned int id = get_global_id( 0 ); "
        "a[ id ]; "
        "size; "
        "}";
    const std::string actual = KERNEL( MyKernel,
        __kernel void MyKernel( __global const float* a, global unsigned int size )
        {
            const unsigned int id = get_global_id( 0 );
            a[ id ];
            size;
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}
