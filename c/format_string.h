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
// Windows: http://msdn.microsoft.com/en-us/library/tcxf1dw6.aspx
// glibc: http://linux.die.net/man/3/fprintf

#ifdef PRIu32
# ifdef _WIN32
#   define SIZE_T_PF "%I" PRIu32
# else
#   define SIZE_T_PF "%zd"
# endif
#else
# define SIZE_T_PF "%u"
#endif

#if SIZEOF_OFF_T == 8
# ifdef PRIu64
#  define OFF_T_PF "%" PRIu64
# else
#  define OFF_T_PF "%llu"
# endif
#else
# ifdef PRIu32
#  define OFF_T_PF "%" PRIu32
# else
#  define OFF_T_PF "%lu"
# endif
#endif
