//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_TEST_MOCK_KERNEL_PROXY_H
#define OPENCLAM_TEST_MOCK_KERNEL_PROXY_H

#include "openclam/ikernel_proxy.hpp"

namespace openclam
{

MOCK_BASE_CLASS( mock_kernel_proxy, ikernel_proxy )
{
    MOCK_METHOD( execute, 4 )
};

}

#endif // #ifndef OPENCLAM_TEST_MOCK_KERNEL_PROXY_H
