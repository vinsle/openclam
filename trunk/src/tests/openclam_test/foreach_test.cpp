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
#include <boost/assign.hpp>

BOOST_AUTO_TEST_CASE( simple_for_each_with_unary_function )
{
    std::vector< unsigned int > actual = boost::assign::list_of( 1 ).repeat( 9, 1 );
    openclam::context context;
    KERNEL( Unary, context, unsigned int,
        kernel void Unary( __global unsigned int* a )
        {
            a[ get_global_id( 0 ) ] += 3;
        } );
    openclam::for_each( actual.begin(), actual.end(), Unary );
    const std::vector< unsigned int > expected = boost::assign::list_of( 4 ).repeat( 9, 4 );
    BOOST_CHECK( actual == expected );
}
