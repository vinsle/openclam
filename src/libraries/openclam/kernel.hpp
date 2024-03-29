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
#include "icontext.hpp"
#include "error.hpp"
#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace openclam
{
template< typename T >
class kernel_base : protected openclam::builtin
{
public:
    kernel_base( const std::string& name, const openclam::icontext& context, const std::string& sources )
        : context_( context )
        , kernel_ ( context.create( name, sources ) )
    {
        // NOTHING
    }
    virtual ~kernel_base()
    {
        // NOTHING
    }
    void operator()( T* data, size_t size )
    {
        context_.execute( data, sizeof( T ) * size, *kernel_ );
    }
protected:
    boost::function< void( T* ) > f_;
private:
    const openclam::icontext& context_;
    std::auto_ptr< openclam::ikernel_proxy > kernel_;
};
}

#define __kernel
#define kernel

#define __global
#define global

#define APPLY_DEFINES( NAME, CONTEXT, TYPE, FUNCTION, SOURCES )             \
class NAME##_CLASS : public openclam::kernel_base< TYPE >                   \
{                                                                           \
public:                                                                     \
    explicit NAME##_CLASS( const openclam::icontext& CONTEXT )              \
                : openclam::kernel_base< TYPE >( #NAME, CONTEXT, SOURCES )  \
             {                                                              \
                type_check();                                               \
                f_ = boost::bind( &NAME##_CLASS::##NAME, this, _1 );        \
             }                                                              \
    virtual ~NAME##_CLASS() {}                                              \
private:                                                                    \
    void type_check(){ TYPE data; NAME( &data ); }                          \
    FUNCTION;                                                               \
} NAME( CONTEXT );

#define KERNEL( NAME, CONTEXT, TYPE, FUNCTION )            \
APPLY_DEFINES( NAME, CONTEXT, TYPE, FUNCTION, #FUNCTION );

#endif // #ifndef OPENCLAM_KERNEL_HPP_INCLUDED
