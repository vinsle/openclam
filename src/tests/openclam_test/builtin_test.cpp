//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/kernel.hpp"
#include "mock_context.h"
#include "mock_kernel_proxy.h"

BOOST_AUTO_TEST_CASE( get_global_id_can_be_called_inside_code_part )
{
    openclam::mock_context context;
    openclam::mock_kernel_proxy* proxy = new openclam::mock_kernel_proxy();
    MOCK_EXPECT( context, create ).once().returns( proxy );
    KERNEL( MyKernel, context, float,
        __kernel void MyKernel( global const float* a )
        {
            get_global_id( 0 );
            a;
        } );
}
