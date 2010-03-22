//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_TEST_MOCK_CONTEXT_H
#define OPENCLAM_TEST_MOCK_CONTEXT_H

#include "openclam/icontext.hpp"

namespace openclam
{

MOCK_BASE_CLASS( mock_context, icontext )
{
    MOCK_METHOD( create, 1 )
    MOCK_METHOD( execute, 3 )
};

}

#endif // #ifndef OPENCLAM_TEST_MOCK_CONTEXT_H
