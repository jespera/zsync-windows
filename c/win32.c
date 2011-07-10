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
// Taken from http://code.google.com/p/googlesitemapgenerator/source/browse/trunk/src/common/timesupport.cc,
// Converted from C++ to C by Pau Garcia i Quiles <pgquiles@elpauer.org>

#include "win32.h"

#ifdef WIN32

#include <time.h>
#include <ctype.h>
#include <string.h>

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
   version 2.1 of the License, or (at your option) any later version.  */

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

      fd = open (tmpl, O_RDWR | O_CREAT | O_EXCL, _S_IREAD | _S_IWRITE);
      if (fd >= 0)
    {
      errno = save_errno;
      return fd;
    }
      else if (errno != EEXIST)
    return -1;
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

//#elif !defined( HAVE_PREAD )
//ssize_t pread(int fd, const void * buf, size_t size, off_t offset) {
//    off_t offs0;
//    ssize_t rd;
//    if ((offs0 = lseek(fd, 0, SEEK_CUR)) == (off_t)-1) return -1;
//    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) return -1;
//    rd = read(fd, (void *)buf, size);
//   if (lseek(fd, offs0, SEEK_SET) == (off_t)-1) return -1;
//    return rd;
//}

ssize_t pwrite(int fd, const void * buf, size_t size, off_t offset) {
    off_t offs0;
    ssize_t wr;
    if ((offs0 = lseek(fd, 0, SEEK_CUR)) == (off_t)-1) return -1;
    if (lseek(fd, offset, SEEK_SET) == (off_t)-1) return -1;
    wr = write(fd, (void *)buf, size);
    if (lseek(fd, offs0, SEEK_SET) == (off_t)-1) return -1;
    return wr;
}

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
