#ifdef _WIN32

#include "win32.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>

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

// Implement strptime under windows
static const char* kWeekFull[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday",
  "Thursday", "Friday", "Saturday"
};

static const char* kWeekAbbr[] = {
  "Sun", "Mon", "Tue", "Wed",
  "Thu", "Fri", "Sat"
};

static const char* kMonthFull[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

static const char* kMonthAbbr[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char* _parse_num(const char* s, int low, int high, int* value) {
  const char* p = s;
  for (*value = 0; *p != NULL && isdigit(*p); ++p) {
    *value = (*value) * 10 + ((int)(*p)) - ((int)('0'));
  }

  if (p == s || *value < low || *value > high) return NULL;
  return p;
}

static char* _strptime(const char *s, const char *format, struct tm *tm) {
  while (*format != NULL && *s != NULL) {
    if (*format != '%') {
      if (*s != *format) return NULL;

      ++format;
      ++s;
      continue;
    }

    ++format;
    int len = 0;
    switch (*format) {
      // weekday name.
      case 'a':
      case 'A':
        tm->tm_wday = -1;
        int i;
        for (i = 0; i < 7; ++i) {
          len = ((int)(strlen(kWeekAbbr[i])));
          if (strnicmp(kWeekAbbr[i], s, len) == 0) {
            tm->tm_wday = i;
            break;
          }

          len = ((int)(strlen(kWeekFull[i])));
          if (strnicmp(kWeekFull[i], s, len) == 0) {
            tm->tm_wday = i;
            break;
          }
        }
        if (tm->tm_wday == -1) return NULL;
        s += len;
        break;
      
      // month name.
      case 'b':
      case 'B':
      case 'h':
        tm->tm_mon = -1;
        int j;
        for (j = 0; j < 12; ++j) {
          len = ((int)(strlen(kMonthAbbr[j])));
          if (strnicmp(kMonthAbbr[j], s, len) == 0) {
            tm->tm_mon = j;
            break;
          }

          len = ((int)(strlen(kMonthFull[j])));
          if (strnicmp(kMonthFull[j], s, len) == 0) {
            tm->tm_mon = j;
            break;
          }
        }
        if (tm->tm_mon == -1) return NULL;
        s += len;
        break;

      // month [1, 12].
      case 'm':
        s = _parse_num(s, 1, 12, &tm->tm_mon);
        if (s == NULL) return NULL;
        --tm->tm_mon;
        break;

      // day [1, 31].
      case 'd':
      case 'e':
        s = _parse_num(s, 1, 31, &tm->tm_mday);
        if (s == NULL) return NULL;
        break;

      // hour [0, 23].
      case 'H':
        s = _parse_num(s, 0, 23, &tm->tm_hour);
        if (s == NULL) return NULL;
        break;

      // minute [0, 59]
      case 'M':
        s = _parse_num(s, 0, 59, &tm->tm_min);
        if (s == NULL) return NULL;
        break;

      // seconds [0, 60]. 60 is for leap year.
      case 'S':
        s = _parse_num(s, 0, 60, &tm->tm_sec);
        if (s == NULL) return NULL;
        break;

      // year [1900, 9999].
      case 'Y':
        s = _parse_num(s, 1900, 9999, &tm->tm_year);
        if (s == NULL) return NULL;
        tm->tm_year -= 1900;
        break;

      // year [0, 99].
      case 'y':
        s = _parse_num(s, 0, 99, &tm->tm_year);
        if (s == NULL) return NULL;
        if (tm->tm_year <= 68) {
          tm->tm_year += 100;
        }
        break;

      // arbitray whitespace.
      case 't':
      case 'n':
        while (isspace(*s)) ++s;
        break;

    case 'z': /* Basic support, enough for zsync */
        tzset();

        if(_daylight > 0) {
            tm->tm_isdst = 1;
        } else {
            tm->tm_isdst = 0;
        }
        break;

      // '%'.
      case '%':
        if (*s != '%') return NULL;
        ++s;
        break;        

      // All the other format are not supported.
      default:
        return NULL;
    }
    ++format;
  }

  if (*format != NULL) {
    return NULL;
  } else {
    return ((char*)(s));
  }
}

char* strptime(const char *buf, const char *fmt, struct tm *tm) {
  return _strptime(buf, fmt, tm);
}


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
   version 2.1 of the License, or (at your option) any later version.

   Modified by Pau Garcia i Quiles to allow renaming the temporary file.
   Unfortunately on Windows allowing rename implies non-exclusive access:
   http://msdn.microsoft.com/en-us/library/aa363858%28v=vs.85%29.aspx

   FILE_SHARE_DELETE "Note  Delete access allows both delete and rename operations."
                     "the dwShareMode parameter must be zero (exclusive access)"
*/

static const char letters[] =
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/* Generate a temporary file name based on TMPL.  TMPL must match the
   rules for mk[s]temp (i.e. end in "XXXXXX").  The name constructed
   does not exist at the time of the call to mkstemp.  TMPL is
   overwritten with the result.  */
int
mkstemp (char *tmpl)
{
  int len;
  char *XXXXXX;
  static unsigned long long value;
  unsigned long long random_time_bits;
  unsigned int count;
  int fd = -1;
  int save_errno = errno;

  /* A lower bound on the number of temporary files to attempt to
     generate.  The maximum total number of temporary file names that
     can exist for a given template is 62**6.  It should never be
     necessary to try all these combinations.  Instead if a reasonable
     number of names is tried (we define reasonable as 62**3) fail to
     give the system administrator the chance to remove the problems.  */
#define ATTEMPTS_MIN (62 * 62 * 62)

  /* The number of times to attempt to generate a temporary file.  To
     conform to POSIX, this must be no smaller than TMP_MAX.  */
#if ATTEMPTS_MIN < TMP_MAX
  unsigned int attempts = TMP_MAX;
#else
  unsigned int attempts = ATTEMPTS_MIN;
#endif

  len = strlen (tmpl);
  if (len < 6 || strcmp (&tmpl[len - 6], "XXXXXX"))
    {
      errno = EINVAL;
      return -1;
    }

/* This is where the Xs start.  */
  XXXXXX = &tmpl[len - 6];

  /* Get some more or less random data.  */
  {
    SYSTEMTIME      stNow;
    FILETIME ftNow;

    // get system time
    GetSystemTime(&stNow);
    stNow.wMilliseconds = 500;
    if (!SystemTimeToFileTime(&stNow, &ftNow))
    {
        errno = -1;
        return -1;
    }

    random_time_bits = (((unsigned long long)ftNow.dwHighDateTime << 32)
                        | (unsigned long long)ftNow.dwLowDateTime);
  }
  value += random_time_bits ^ (unsigned long long)GetCurrentThreadId ();

  for (count = 0; count < attempts; value += 7777, ++count)
    {
      unsigned long long v = value;

      /* Fill in the random bits.  */
      XXXXXX[0] = letters[v % 62];
      v /= 62;
      XXXXXX[1] = letters[v % 62];
      v /= 62;
      XXXXXX[2] = letters[v % 62];
      v /= 62;
      XXXXXX[3] = letters[v % 62];
      v /= 62;
      XXXXXX[4] = letters[v % 62];
      v /= 62;
      XXXXXX[5] = letters[v % 62];

      /* On Windows, open(2) locks the file. A bit of imagination is required to be able to rename the temporary file. */
      /* fd = open (tmpl, O_RDWR | O_CREAT | O_EXCL, _S_IREAD | _S_IWRITE); */
      HANDLE hFile = CreateFile(tmpl,
                                GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                NULL,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_POSIX_SEMANTICS,
                                NULL );
      if( INVALID_HANDLE_VALUE == hFile) {
          errno = EINVAL;
          return -1;
      }

      int fd = _open_osfhandle((long int)hFile, _O_CREAT | _O_RDWR | _O_TEMPORARY);

      if (fd >= 0)
      {
        errno = save_errno;
        return fd;
      } else if (errno != EEXIST) {
        return -1;
      }
    }

  /* We got out of the loop because we ran out of combinations to try.  */
  errno = EEXIST;
  return -1;
}

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

ssize_t pread (int fd, void *buf, size_t count, off_t offset)
{
    HANDLE handle = (HANDLE)(intptr_t)_get_osfhandle (fd);
    if (handle == INVALID_HANDLE_VALUE)
        return -1;

    OVERLAPPED olap; olap.Offset = offset; olap.OffsetHigh = (offset >> 32);
    DWORD written;
    /* This braindead API will override the file pointer even if we specify
     * an explicit read offset... So do not expect this to mix well with
     * regular read() calls. */
    if (ReadFile (handle, buf, count, &written, &olap))
        return written;
    return -1;
}

/*
ssize_t pwrite(int fd, const void * buf, size_t size, off_t offset) {
    off_t offs0;
    ssize_t wr;
    if ((offs0 = lseek(fd, 0, SEEK_CUR)) == (off_t)-1) return -1;
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) return -1;
    wr = write(fd, (void *)buf, size);
    if (lseek(fd, offs0, SEEK_SET) == (off_t)-1) return -1;
    return wr;
}
*/
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

struct tm *gmtime_r (const time_t *timep, struct tm *result)
{
    struct tm *s = gmtime (timep);
    if (s == NULL)
        return NULL;

    *result = *s;
    return result;
}
#endif  // WIN32


/*********************************************************************
 *********************************************************************
 *********************************************************************/

//////////////////////////////////////////////////////////////////////////////////////////
//   w32util.c        Windows porting functions
//////////////////////////////////////////////////////////////////////////////////////////
// (c) Copyright "Fish" (David B. Trout), 2005-2009. Released under the Q Public License
// (http://www.hercules-390.org/herclic.html) as modifications to Hercules.
//////////////////////////////////////////////////////////////////////////////////////////

#if defined(DEBUG) || defined(_DEBUG)

  #ifdef _MSC_VER

    #define TRACE(...) \
      do \
      { \
        IsDebuggerPresent() ? DebugTrace (__VA_ARGS__): \
                              logmsg     (__VA_ARGS__); \
      } \
      while (0)

    #undef ASSERT /* For VS9 2008 */
    #define ASSERT(a) \
      do \
      { \
        if (!(a)) \
        { \
          TRACE("HHCxx999W *** Assertion Failed! *** %s(%d); function: %s\n",__FILE__,__LINE__,__FUNCTION__); \
          if (IsDebuggerPresent()) DebugBreak();   /* (break into debugger) */ \
        } \
      } \
      while(0)

  #else // ! _MSC_VER

    #define TRACE logmsg

    #define ASSERT(a) \
      do \
      { \
        if (!(a)) \
        { \
          TRACE("HHCxx999W *** Assertion Failed! *** %s(%d)\n",__FILE__,__LINE__); \
        } \
      } \
      while(0)

  #endif // _MSC_VER

  #define VERIFY  ASSERT

#else // non-debug build...

  #ifdef _MSVC_

    #define TRACE       __noop
    #undef ASSERT /* For VS9 2008 */
    #define ASSERT(a)   __noop
    #define VERIFY(a)   ((void)(a))

  #else // ! _MSVC_

    #define TRACE       1 ? ((void)0) : logmsg
    #define ASSERT(a)
    #define VERIFY(a)   ((void)(a))

  #endif // _MSVC_

#endif

SOCKET PASCAL w32_socket( int af, int type, int protocol )
{
    ///////////////////////////////////////////////////////////////////////////////
    //
    //                         PROGRAMMING NOTE
    //
    // We need to request that all sockets we create [via the 'socket()' API]
    // be created WITHOUT the "OVERLAPPED" attribute so that our 'fgets()', etc,
    // calls (which end up calling the "ReadFile()", etc, Win32 API) work as
    // expected.
    //
    // Note that the "overlapped" attribute for a socket is completely different
    // from its non-blocking vs. blocking mode. All sockets are created, by default,
    // as blocking mode sockets, but WITH the "overlapped" attribute set. Thus all
    // sockets are actually asynchonous by default. (The winsock DLL(s) handle the
    // blocking mode separately programmatically internally even though the socket
    // is actually an asynchronous Win32 "file").
    //
    // Thus we need to specifically request that our [blocking mode] sockets be
    // created WITHOUT the Win32 "OVERLAPPED" attribute (so that when we call the
    // C runtime read/write/etc functions, the C runtime's ReadFile/WriteFile calls
    // work (which they don't (they fail with error 87 ERROR_INVALID_PARAMETER)
    // when called on a Win32 "file" handle created with the OVERLAPPED attribute
    // but without an OVERLAPPED structure pased in the ReadFile/WriteFile call
    // (which the C runtime functions don't use)). You follow?).
    //
    // See KB (Knowledge Base) article 181611 for more information:
    //
    //        "Socket overlapped I/O versus blocking/non-blocking mode"
    //            (http://support.microsoft.com/?kbid=181611)
    //
    //  ---------------------------------------------------------------------
    //   "However, you can call the setsockopt API with SO_OPENTYPE option
    //   on any socket handle -- including an INVALID_SOCKET -- to change
    //   the overlapped attributes for all successive socket calls in the
    //   same thread. The default SO_OPENTYPE option value is 0, which sets
    //   the overlapped attribute. All non-zero option values make the socket
    //   synchronous and make it so that you cannot use a completion function."
    //  ---------------------------------------------------------------------
    //
    // The documentation for the "SOL_SOCKET" SO_OPENTYPE socket option contains
    // the folowing advice/warning however:
    //
    //
    //    "Once set, subsequent sockets created will be non-overlapped.
    //     This option should not be used; use WSASocket and leave the
    //     WSA_FLAG_OVERLAPPED turned off."
    //
    //
    // So we'll use WSASocket instead as suggested.
    //
    ///////////////////////////////////////////////////////////////////////////////

    // The last parameter is where one would normally specify the WSA_FLAG_OVERLAPPED
    // option, but we're specifying '0' because we want our sockets to be synchronous
    // and not asynchronous so the C runtime functions can successfully perform ReadFile
    // and WriteFile on them...

    SOCKET sock = WSASocket( af, type, protocol, NULL, 0, 0 );

    if ( INVALID_SOCKET == sock )
    {
        errno = WSAGetLastError();
        sock = (SOCKET) -1;
    }

    return ( (int) sock );
}

struct MODE_TRANS
{
    const char*  old_mode;
    const char*  new_mode;
    int          new_flags;
};

typedef struct MODE_TRANS MODE_TRANS;


/*
   Microsoft's (therefore MinGW's too) fdopen cannot open socket file
   descriptors directly, which leads http_get_stream to crash.

   It is possible to solve this issue by calling _open_osfhandle as an
   intermediate step.

   http://www.codeguru.com/forum/showthread.php?t=395678
   http://msdn.microsoft.com/en-us/library/ms740096
   http://oldwiki.mingw.org/index.php/sockets

   Modified by Pau Garcia i Quiles <pgquiles@elpauer.org> to support
   'rb', 'wb' and 'ab' modes

   */

FILE* w32_fdopen( int their_fd, const char* their_mode )
{
    int new_fd, new_flags = 0;
    const char* new_mode = NULL;
    MODE_TRANS* pModeTransTab;
    MODE_TRANS  mode_trans_tab[] =
    {
        { "r",   "rbc",  _O_RDONLY                        | _O_BINARY },
        { "rb",  "rbc",  _O_RDONLY                        | _O_BINARY },
        { "r+",  "r+bc", _O_RDWR                          | _O_BINARY },
        { "r+b", "r+bc", _O_RDWR                          | _O_BINARY },
        { "rb+", "r+bc", _O_RDWR                          | _O_BINARY },

        { "w",   "wbc",  _O_WRONLY | _O_CREAT | _O_TRUNC  | _O_BINARY },
        { "wb",  "wbc",  _O_WRONLY | _O_CREAT | _O_TRUNC  | _O_BINARY },
        { "w+",  "w+bc", _O_RDWR   | _O_CREAT | _O_TRUNC  | _O_BINARY },
        { "w+b", "w+bc", _O_RDWR   | _O_CREAT | _O_TRUNC  | _O_BINARY },
        { "wb+", "w+bc", _O_RDWR   | _O_CREAT | _O_TRUNC  | _O_BINARY },

        { "a",   "abc",  _O_WRONLY | _O_CREAT | _O_APPEND | _O_BINARY },
        { "ab",  "abc",  _O_WRONLY | _O_CREAT | _O_APPEND | _O_BINARY },
        { "a+",  "a+bc", _O_RDWR   | _O_CREAT | _O_APPEND | _O_BINARY },
        { "a+b", "a+bc", _O_RDWR   | _O_CREAT | _O_APPEND | _O_BINARY },
        { "ab+", "a+bc", _O_RDWR   | _O_CREAT | _O_APPEND | _O_BINARY },

        { NULL, NULL, 0 }
    };

    ASSERT( their_mode );

    // (we're only interested in socket calls)

    if ( !socket_is_socket( their_fd ) )
        return _fdopen( their_fd, their_mode );

    // The passed "file descriptor" is actually a SOCKET handle...

    // Translate their original mode to our new mode
    // and determine what flags we should use in our
    // call to _open_osfhandle()...

    if ( their_mode )
        for (pModeTransTab = mode_trans_tab; pModeTransTab->old_mode; pModeTransTab++)
            if ( strcmp( their_mode, pModeTransTab->old_mode ) == 0 )
            {
                new_mode  = pModeTransTab->new_mode;
                new_flags = pModeTransTab->new_flags;
                break;
            }

    if ( !new_mode )
    {
        errno = EINVAL;
        return NULL;
    }

    // Allocate a CRT file descriptor integer for this SOCKET...

    if ( ( new_fd = _open_osfhandle( their_fd, new_flags ) ) < 0 )
        return NULL;  // (errno already set)

    // Now we should be able to do the actual fdopen...

    return _fdopen( new_fd, new_mode );
}

//////////////////////////////////////////////////////////////////////////////////////////
// fclose
int w32_fclose ( FILE* stream )
{
    int sd, rc, err;
    SOCKET sock;

    ASSERT( stream );

    sd = fileno( stream );

    if ( !socket_is_socket( sd ) )
        return fclose( stream );

    // (SOCKETs get special handling)

    sock = (SOCKET) _get_osfhandle( sd );

    // Flush the data, close the socket, then deallocate
    // the crt's file descriptor for it by calling fclose.

    // Note that the fclose will fail since the closesocket
    // has already closed the o/s handle, but we don't care;
    // all we care about is the crt deallocating its file
    // descriptor for it...

    fflush( stream );               // (flush buffers)
    shutdown( sock, SD_BOTH);       // (try to be graceful)
    rc  = closesocket( sock );      // (close socket)
    err = WSAGetLastError();        // (save retcode)
    fclose( stream );               // (ignore likely error)

    if ( SOCKET_ERROR == rc )       // (closesocket error?)
    {
        errno = err;                // (yes, return error)
        return EOF;                 // (failed)
    }
    return 0;                       // (success)
}

//////////////////////////////////////////////////////////////////////////////////////////
// Determine whether a file descriptor is a socket or not...
// (returns 1==true if it's a socket, 0==false otherwise)
int socket_is_socket( int sfd )
{
    u_long dummy;
    return WSAHtonl( (SOCKET) sfd, 666, &dummy ) == 0 ? 1 : 0;
}



#include <windows.h>
#include <io.h>


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
FILE *
w32_tmpfile (void)
{
    DWORD path_len;
    WCHAR path_name[MAX_PATH + 1];
    WCHAR file_name[MAX_PATH + 1];
    HANDLE handle;
    int fd;
    FILE *fp;

    path_len = GetTempPathW (MAX_PATH, path_name);
    if (path_len <= 0 || path_len >= MAX_PATH)
        return NULL;

    if (GetTempFileNameW (path_name, L"ps_", 0, file_name) == 0)
        return NULL;

    handle = CreateFileW (file_name,
                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         NULL,
                         CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL | FILE_FLAG_DELETE_ON_CLOSE,
                         NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        DeleteFileW (file_name);
        return NULL;
    }

    fd = _open_osfhandle((intptr_t) handle, 0);
    if (fd < 0) {
        CloseHandle (handle);
        return NULL;
    }

    fp = fdopen(fd, "w+b");
    if (fp == NULL) {
        _close(fd);
        return NULL;
    }

    return fp;
}
