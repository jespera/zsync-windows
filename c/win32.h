#ifndef H_WIN32
#define H_WIN32

#ifdef _WIN32

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <time.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>

// Copyright 2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Taken from http://code.google.com/p/googlesitemapgenerator/source/browse/trunk/src/common/timesupport.h,
// Converted from C++ to C, and basic support for timezones, by Pau Garcia i Quiles <pgquiles@elpauer.org>

// Convert a string representation time to a time tm structure.
// It is the conversion function of strftime().
// Linux provides this function.
char *strptime(const char *buf, const char *fmt, struct tm *tm);


/*********************************************************************
 *********************************************************************
 *********************************************************************/


/*  wcecompat: Windows CE C Runtime Library "compatibility" library.
 *
 *  Copyright (C) 2001-2002 Essemer Pty Ltd.  All rights reserved.
 *  http://www.essemer.com.au/
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* mkstemp extracted from libc/sysdeps/posix/tempname.c.  Copyright
   (C) 1991-1999, 2000, 2001, 2006 Free Software Foundation, Inc.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.  */

/* Generate a temporary file name based on TMPL.  TMPL must match the
   rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
   does not exist at the time of the call to mkstemp.  TMPL is
   overwritten with the result.  */

int mkstemp (char *tmpl);

#ifndef EEXIST
#define EEXIST          17
#endif

#ifndef EINVAL
#define EINVAL          22
#endif

#define _O_RDWR			0x0002
#define O_RDWR			_O_RDWR

#define _O_CREAT		0x0100
#define O_CREAT			_O_CREAT

#define _O_EXCL         0x0400
#define O_EXCL          _O_EXCL

//#define _S_IREAD        0000400         /* read permission, owner */
//#define _S_IWRITE       0000200         /* write permission, owner */
#define S_IREAD			_S_IREAD
#define S_IWRITE		_S_IWRITE


/*********************************************************************
 *********************************************************************
 *********************************************************************/

 
/*****************************************************************************
 * block.c: Data blocks management functions
 *****************************************************************************
 * Copyright (C) 2003-2004 the VideoLAN team
 * Copyright (C) 2007-2009 Rémi Denis-Courmont
 *
 * Authors: Laurent Aimar <fenrir@videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

ssize_t pread (int fd, void *buf, size_t count, off_t offset);

#ifndef HAVE_GMTIME_R
/*****************************************************************************
 * gmtime_r.c: POSIX gmtime_r() replacement
 *****************************************************************************
 * Copyright © 1998-2008 the VideoLAN project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
struct tm *gmtime_r (const time_t *timep, struct tm *result);
#endif // HAVE_GMTIME_R

//////////////////////////////////////////////////////////////////////////////////////////
//   w32util.c        Windows porting functions
//////////////////////////////////////////////////////////////////////////////////////////
// (c) Copyright "Fish" (David B. Trout), 2005-2009. Released under the Q Public License
// (http://www.hercules-390.org/herclic.html) as modifications to Hercules.
//////////////////////////////////////////////////////////////////////////////////////////

SOCKET PASCAL w32_socket( int af, int type, int protocol );

FILE* w32_fdopen( int their_fd, const char* their_mode );

int w32_fclose ( FILE* stream );

int socket_is_socket( int sfd );


/*********************************************************************
 *********************************************************************
 *********************************************************************/

/* Cairo - a vector graphics library with display and print output
 *
 * Copyright © 2007 Adrian Johnson
 *
 * This library is free software; you can redistribute it and/or
 * modify it either under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * (the "LGPL") or, at your option, under the terms of the Mozilla
 * Public License Version 1.1 (the "MPL"). If you do not alter this
 * notice, a recipient may use your version of this file under either
 * the MPL or the LGPL.
 *
 * You should have received a copy of the LGPL along with this library
 * in the file COPYING-LGPL-2.1; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * You should have received a copy of the MPL along with this library
 * in the file COPYING-MPL-1.1
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY
 * OF ANY KIND, either express or implied. See the LGPL or the MPL for
 * the specific language governing rights and limitations.
 *
 * The Original Code is the cairo graphics library.
 *
 * The Initial Developer of the Original Code is Adrian Johnson.
 *
 * Contributor(s):
 *      Adrian Johnson <ajohnson@redneon.com>
 */

/* tmpfile() replacement for Windows.
 *
 * On Windows tmpfile() creates the file in the root directory. This
 * may fail due to unsufficient privileges.
 */
FILE * w32_tmpfile (void);

#endif // _WIN32

#endif // H_WIN32
