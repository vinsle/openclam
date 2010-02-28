//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_ERROR_HPP_INCLUDED
#define OPENCLAM_ERROR_HPP_INCLUDED

#pragma warning( push )
#pragma warning( disable: 4702 )
#include <boost/lexical_cast.hpp>
#pragma warning( pop )

#define ERROR_HANDLER( CODE )   \
{                               \
    cl_int ERROR;               \
    CODE;                        \
    if( ERROR != CL_SUCCESS )   \
        throw std::runtime_error( "Openclam error '" + boost::lexical_cast< std::string >( ERROR ) + "' at : '" + #CODE ); \
}

#endif // #ifndef OPENCLAM_ERROR_HPP_INCLUDED