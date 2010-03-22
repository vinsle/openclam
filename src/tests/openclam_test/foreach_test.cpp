//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/kernel.hpp"
#include "openclam/for_each.hpp"
#include "mock_context.h"
#include "mock_kernel_proxy.h"
#include "mock_program.h"
#include <vector>
#include <list>
#include <boost/assign.hpp>

namespace
{
    class fixture
    {
    public:
        fixture()
        {
            openclam::mock_kernel_proxy* proxy = new openclam::mock_kernel_proxy();
            openclam::mock_program* program = new openclam::mock_program();
            MOCK_EXPECT( *program, create ).once().with( "Unary" ).returns( proxy );
            MOCK_EXPECT( context, create ).once().returns( program );
        }
        openclam::mock_context context;
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
    MOCK_EXPECT( context, execute ).once().with( &actual[ 0 ], sizeof( unsigned int ) * actual.size(), mock::any );
    openclam::for_each( actual.begin(), actual.end(), Unary );
}

BOOST_FIXTURE_TEST_CASE( for_each_with_unary_function_on_list_data, fixture )
{
    KERNEL( Unary, context, float,
        kernel void Unary( __global float* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    std::list< float > actual = boost::assign::list_of( 1.f ).repeat( 9, 1.f );
    MOCK_EXPECT( context, execute ).once().with( mock::any, sizeof( float ) * actual.size(), mock::any );
    openclam::for_each( actual.begin(), actual.end(), Unary );
}
