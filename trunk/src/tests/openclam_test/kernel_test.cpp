//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/cl.hpp"

BOOST_AUTO_TEST_CASE( kernel_keyword_substitution_test )
{
    const std::string expected =
        "kernel void MyKernel() "
        "{ "
        "}";
    const std::string actual = KERNEL( MyKernel,
        kernel void MyKernel()
        {
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}

BOOST_AUTO_TEST_CASE( __kernel_keyword_substitution_test )
{
    const std::string expected =
        "__kernel void MyKernel() "
        "{ "
        "}";
    const std::string actual = KERNEL( MyKernel,
        __kernel void MyKernel()
        {
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}

BOOST_AUTO_TEST_CASE( global_keyword_substitution_test )
{
    const std::string expected =
        "__kernel void MyKernel( global const float* a ) "
        "{ "
        "a; "
        "}";
    const std::string actual = KERNEL( MyKernel,
        __kernel void MyKernel( global const float* a )
        {
            a;
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}

BOOST_AUTO_TEST_CASE( __global_keyword_substitution_test )
{
    const std::string expected =
        "__kernel void MyKernel( __global const float* a ) "
        "{ "
        "a; "
        "}";
    const std::string actual = KERNEL( MyKernel,
        __kernel void MyKernel( __global const float* a )
        {
            a;
        } );
    BOOST_CHECK_EQUAL( actual, expected );
}
