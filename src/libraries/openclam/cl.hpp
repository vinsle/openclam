//
//  Copyright Silvin Lubecki 2010
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef OPENCLAM_CL_HPP_INCLUDED
#define OPENCLAM_CL_HPP_INCLUDED

int get_global_id( unsigned int index );

#define GLOBAL __global

#define COMPILE( SOURCES ) SOURCES;

#define APPLY_DEFINES( VARIABLE, SOURCES ) VARIABLE = #SOURCES

#define KERNEL( VARIABLE, SOURCES ) \
        APPLY_DEFINES( VARIABLE, __kernel SOURCES )

#endif // #ifndef OPENCLAM_CL_HPP_INCLUDED
