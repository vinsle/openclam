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
#include "program.hpp"
#include "error.hpp"
#include <string>

namespace openclam
{
class kernel_base : protected openclam::builtin
{
public:
             kernel_base( const std::string& name, const openclam::context& context, const std::string& sources )
                 : context_( context )
                 , program_( context_.create( sources ) )
                 , kernel_ ( program_->create( name ) )
             {}
    virtual ~kernel_base()
             {
                 clReleaseKernel( kernel_ ); // $$$$ 28-02-2010 SILVIN: check error code?
             }
    template< typename T >
    void operator()( T*& data, size_t size )
    {
        context_.execute( data, size, kernel_ );
    }
private:
    const openclam::context& context_;
    std::auto_ptr< openclam::program > program_;
    cl_kernel kernel_;
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
