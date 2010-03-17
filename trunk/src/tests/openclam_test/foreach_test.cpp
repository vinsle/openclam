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

BOOST_AUTO_TEST_CASE( for_each_with_unary_function_on_vector_data )
{
    std::vector< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::opencl wrapper;
    openclam::context context( wrapper );
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    openclam::for_each( actual.begin(), actual.end(), Unary );
    const std::vector< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}

BOOST_AUTO_TEST_CASE( for_each_with_unary_function_on_list_data )
{
    std::list< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::opencl wrapper;
    openclam::context context( wrapper );
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    openclam::for_each( actual.begin(), actual.end(), Unary );
    const std::list< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}

BOOST_AUTO_TEST_CASE( use_of_stl_for_each_with_vector_data )
{
    std::vector< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::opencl wrapper;
    openclam::context context( wrapper );
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    std::for_each( actual.begin(), actual.end(), openclam::unary_function< unsigned int, Unary_CLASS >( Unary ) );
    const std::vector< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}

BOOST_AUTO_TEST_CASE( use_of_stl_for_each_with_list_data )
{
    std::list< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::opencl wrapper;
    openclam::context context( wrapper );
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    std::for_each( actual.begin(), actual.end(), openclam::unary_function< unsigned int, Unary_CLASS >( Unary ) );
    const std::list< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}
