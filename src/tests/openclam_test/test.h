//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_TEST_TEST_H_INCLUDED
#define OPENCLAM_TEST_TEST_H_INCLUDED

#include <boost/test/auto_unit_test.hpp>
#define BOOST_LIB_NAME boost_unit_test_framework
#include <boost/config/auto_link.hpp>

#include <turtle/mock.hpp>
#pragma warning( disable : 4505 ) // unreferenced local function has been removed

std::string BOOST_RESOLVE( const std::string& filename );

#endif // #ifndef OPENCLAM_TEST_TEST_H_INCLUDED
