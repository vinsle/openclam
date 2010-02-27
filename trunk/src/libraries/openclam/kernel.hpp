//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_KERNEL_HPP_INCLUDED
#define OPENCLAM_KERNEL_HPP_INCLUDED

#include "builtin.hpp"

#define __kernel
#define kernel

#define __global
#define global

#define APPLY_DEFINES( NAME, FUNCTION )      \
class NAME_CLASS : private openclam::builtin \
{                                            \
private:                                     \
             NAME_CLASS() {}                 \
    virtual ~NAME_CLASS() {}                 \
                                             \
    FUNCTION;                                \
};                                           \

#define KERNEL( NAME, FUNCTION ) \
#FUNCTION;                       \
APPLY_DEFINES( NAME, FUNCTION );

#endif // #ifndef OPENCLAM_KERNEL_HPP_INCLUDED
