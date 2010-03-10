//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_UNARY_FUNCTION_HPP_INCLUDED
#define OPENCLAM_UNARY_FUNCTION_HPP_INCLUDED

#include <functional>

namespace openclam
{

template< typename T, typename Kernel >
struct unary_function : public std::unary_function< T, void >
{
public:
    explicit unary_function( Kernel& k )
        : kernel_( &k )
    {}
    virtual ~unary_function()
    {
        if( kernel_ && !buffer_.empty() )
            (*kernel_)( buffer_[ 0 ], buffer_.size() ); // kernel call can throw in destructor...
    }
    void operator()( T& value )
    {
        buffer_.push_back( &value );
    }
    unary_function( const unary_function& )
        : kernel_( 0 )
    {
        // NOTHING
    }
private:
    Kernel* kernel_;
    std::vector< T* > buffer_;
};

}

#endif // #ifndef OPENCLAM_UNARY_FUNCTION_HPP_INCLUDED
