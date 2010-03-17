//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/cl.hpp"
#include <vector>
#include <list>
#include <boost/assign.hpp>

namespace
{
    class fixture
    {
    public:
        fixture()
            : context( wrapper )
        {}
        openclam::opencl wrapper;
        openclam::context context;
    };
}

BOOST_FIXTURE_TEST_CASE( for_each_with_unary_function_on_vector_data, fixture )
{
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    std::vector< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::for_each( actual.begin(), actual.end(), Unary );
    const std::vector< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}

BOOST_FIXTURE_TEST_CASE( for_each_with_unary_function_on_list_data, fixture )
{
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    std::list< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::for_each( actual.begin(), actual.end(), Unary );
    const std::list< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}
