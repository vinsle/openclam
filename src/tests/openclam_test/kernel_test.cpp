//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/cl.hpp"

//BOOST_AUTO_TEST_CASE( kernel_keyword_is_a_valid_identifier ) // $$$$ 27-02-2010 SILVIN: uncomment this test related to issue 1 (http://code.google.com/p/openclam/issues/detail?id=1)
//{
//    const std::string kernel   = "";
//    const std::string __kernel = "";
//    const std::string global   = "";
//    const std::string __global = "";
//}

namespace
{
    class fixture
    {
    public:
        openclam::context context;
    };
}

BOOST_FIXTURE_TEST_CASE( kernel_keyword_substitution_test, fixture )
{
    KERNEL( MyKernel, context,
        kernel void MyKernel( global const float* a )
        {
        } );
}

BOOST_FIXTURE_TEST_CASE( __kernel_keyword_substitution_test, fixture )
{
    KERNEL( MyKernel, context,
        __kernel void MyKernel( global const float* a )
        {
        } );
}

BOOST_FIXTURE_TEST_CASE( global_keyword_substitution_test, fixture )
{
    KERNEL( MyKernel, context,
        __kernel void MyKernel( global const float* a )
        {
            a;
        } );
}

BOOST_FIXTURE_TEST_CASE( __global_keyword_substitution_test, fixture )
{
    KERNEL( MyKernel, context,
        __kernel void MyKernel( __global const float* a )
        {
            a;
        } );
}
