//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_CL_HPP_INCLUDED
#define OPENCLAM_CL_HPP_INCLUDED

#include <CL/cl.h>
#include "error.hpp"
#include "context.hpp"
#include "builtin.hpp"

#define __kernel
#define kernel

#define __global
#define global

#define APPLY_DEFINES( NAME, SOURCES )      \
class NAME_CLASS : public openclam::builtin \
{                                           \
private:                                    \
             NAME_CLASS() {}                \
    virtual ~NAME_CLASS() {}                \
                                            \
    SOURCES;                                \
};                                          \

#define KERNEL( NAME, SOURCES ) \
#SOURCES;                       \
APPLY_DEFINES( NAME, SOURCES );

#endif // #ifndef OPENCLAM_CL_HPP_INCLUDED
