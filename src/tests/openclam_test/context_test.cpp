//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include "test.h"
#include "openclam/cl.hpp"

BOOST_AUTO_TEST_CASE( simple_context_instanciation )
{
    openclam::context context;
}

BOOST_AUTO_TEST_CASE( context_throws_error_depending_on_available_device_type )
{
    BOOST_CHECK_NO_THROW( openclam::context context );
    BOOST_CHECK_NO_THROW( openclam::context context( openclam::context::default ) );
    BOOST_CHECK_NO_THROW( openclam::context context( openclam::context::all ) );
    BOOST_CHECK_NO_THROW( openclam::context context( openclam::context::gpu ) );
    BOOST_CHECK_THROW( openclam::context context( openclam::context::cpu ), std::runtime_error );
    BOOST_CHECK_THROW( openclam::context context( openclam::context::accelerator ), std::runtime_error );
}
