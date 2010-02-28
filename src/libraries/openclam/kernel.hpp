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
#include "context.hpp"
#include <string>

namespace openclam
{
class kernel_base : protected openclam::builtin
{
public:
             kernel_base( const std::string& name, const openclam::context& context, const std::string& sources )
                : name_   ( name )
                , context_( context )
                , sources_( sources )
             {}
    virtual ~kernel_base() {}
protected:
    const std::string name_;
    const openclam::context& context_;
    const std::string sources_;
};
}

#define __kernel
#define kernel

#define __global
#define global

#define APPLY_DEFINES( NAME, CONTEXT, FUNCTION, SOURCES )    \
class NAME##_CLASS : public openclam::kernel_base            \
{                                                            \
public:                                                      \
    explicit NAME##_CLASS( const openclam::context& CONTEXT )\
    : openclam::kernel_base( #NAME, CONTEXT, SOURCES )       \
             {}                                              \
    virtual ~NAME##_CLASS() {}                               \
private:                                                     \
    FUNCTION;                                                \
} NAME( CONTEXT );

#define KERNEL( NAME, CONTEXT, FUNCTION )            \
APPLY_DEFINES( NAME, CONTEXT, FUNCTION, #FUNCTION );

#endif // #ifndef OPENCLAM_KERNEL_HPP_INCLUDED
