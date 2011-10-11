/*
 *   zsync - client side rsync over http
 *   Copyright (C) 2004,2005 Colin Phipps <cph@moria.org.uk>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the Artistic License v2 (see the accompanying 
 *   file COPYING for the full license terms), or, at your option, any later 
 *   version of the same license.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   COPYING file for details.
 */

#include <inttypes.h>
#include "config.h"

// TODO Check with http://stackoverflow.com/questions/586928/how-should-i-print-types-like-off-t-and-size-t

#ifdef PRIu32
# ifdef __MINGW32__ // All Win32? Does %lu make sense or should I leave %zd?
#  define SIZE_T_PF "%lu"
# else
#  define SIZE_T_PF "%zd"
# endif
#else
# define SIZE_T_PF "%u"
#endif

#if SIZEOF_OFF_T == 8
# ifdef PRIu64
#  warning "Using OFF_T_PF = % PRIu64"
#  define OFF_T_PF "%" PRIu64
# else
#  warning "Using OFF_T_PF = %llu"
#  define OFF_T_PF "%llu"
# endif
#else
# ifdef PRIu32
#  warning "Using OFF_T_PF = % PRIu32"
#  define OFF_T_PF "%" PRIu32
# else
#  warning "Using OFF_T_PF = %lu"
#  define OFF_T_PF "%lu"
# endif
#endif

