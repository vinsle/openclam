//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/cl.hpp"

BOOST_AUTO_TEST_CASE( get_global_id_can_be_called_inside_code_part )
{
    const std::string expected =
        "__kernel void MyKernel() "
        "{ "
        "const unsigned int id = get_global_id( 0 ); "
        "id; "
        "}";
    const std::string actual = KERNEL( MyKernel,
        __kernel void MyKernel()
        {
            const unsigned int id = get_global_id( 0 );
            id;
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}
