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
        if( kernel_ && !data_.empty() )
        {
            (*kernel_)( &data_[ 0 ], data_.size() ); // kernel call can throw in destructor...
            for( unsigned int i = 0; i < data_.size(); ++i )
                *data_references_[ i ] = data_[ i ];
        }
    }
    void operator()( T& value )
    {
        data_.push_back( value );
        data_references_.push_back( &value );
    }
    unary_function( const unary_function& )
        : kernel_( 0 )
    {
        // NOTHING
    }
private:
    Kernel* kernel_;
    std::vector< T > data_;
    std::vector< T* > data_references_;
};

}

#endif // #ifndef OPENCLAM_UNARY_FUNCTION_HPP_INCLUDED
