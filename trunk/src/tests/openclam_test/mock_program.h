//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_TEST_MOCK_PROGRAM_H
#define OPENCLAM_TEST_MOCK_PROGRAM_H

#include "openclam/iprogram.hpp"

namespace openclam
{

MOCK_BASE_CLASS( mock_program, iprogram )
{
    MOCK_METHOD( create, 1 )
};

}

#endif // #ifndef OPENCLAM_TEST_MOCK_PROGRAM_H
