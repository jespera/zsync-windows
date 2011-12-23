#ifndef H_CONFIG
#define H_CONFIG

#cmakedefine HAVE_FSEEKO 1

#cmakedefine FSEEKO_REPLACEMENT 1
#ifdef FSEEKO_REPLACEMENT
#  define fseeko @FSEEKO_REPLACEMENT@
#endif

/* Define to 1 if you have the `getaddrinfo' function. */
#cmakedefine HAVE_GETADDRINFO 1

/* Define to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H 1

/* Define to 1 if you have the `socket' library (-lsocket). */
#cmakedefine HAVE_LIBSOCKET 1

/* Define to 1 if you have the `memcpy' function. */
#cmakedefine HAVE_MEMCPY 1

/* Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H 1

/* Define to 1 if you have the <utime.h> header file. */
#cmakedefine HAVE_UTIME_H 1

/* Define to 1 if you have the `mkstemp' function. */
#cmakedefine HAVE_MKSTEMP 1

/* Define to 1 if you have the `pread' function. */
#cmakedefine HAVE_PREAD 1

/* Define to 1 if you have the `pwrite' function. */
#cmakedefine HAVE_PWRITE 1

/* Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H 1

/* Define to 1 if `h_errno' is declared by <netdb.h> */
#cmakedefine H_ERRNO_DECLARED 1

/* Name of package */
#define PACKAGE "@PACKAGE@"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "@PACKAGE_BUGREPORT@"

/* Define to the full name of this package. */
#define PACKAGE_NAME "@PACKAGE_NAME@"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "@PACKAGE_STRING@"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "@PACKAGE_TARNAME@"

/* Define to the home page for this package. */
#define PACKAGE_URL "@PACKAGE_URL@"

/* Define to the version of this package. */
#define PACKAGE_VERSION "@PACKAGE_VERSION@"

/* The size of `off_t', as computed by sizeof. */
@SIZEOF_OFF_T_CODE@

/* The size of `size_t', as computed by sizeof. */
@SIZEOF_SIZE_T_CODE@

#cmakedefine SIZE_T_REPLACEMENT 1
#ifdef SIZE_T_REPLACEMENT
#  define size_t @SIZE_T_REPLACEMENT@
#endif

/* Define to 1 if you have the ANSI C header files. */
/* #undef STDC_HEADERS */

/* Version number of package */
#define VERSION "@VERSION@"

/* Define if using the dmalloc debugging malloc package */
#cmakedefine WITH_DMALLOC 1

/* Enable BSD extensions if present */
#cmakedefine _BSD_SOURCE @_BSD_SOURCE@

/* Number of bits in a file offset, on hosts where this is settable. */
#cmakedefine _FILE_OFFSET_BITS @_FILE_OFFSET_BITS@

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
#cmakedefine _LARGEFILE_SOURCE @_LARGEFILE_SOURCE@

/* Define for large files, on AIX-style hosts. */
#cmakedefine _LARGE_FILES @_LARGE_FILES@

/*
#if defined(_WIN32) && defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS == 64
#  warning "USING REPLACEMENT FUNCTIONS FOR LFF"
#  define fseeko fseeko64
#  define ftello ftello64
//#  define lseek _lseeki64
#  undef stat
//#  define stat _stati64
//#  define fstat _fstati64
#  define wstat _wstati64
   typedef long long _off64_t;
#  define _off64_t off_t
#else
#  define fseeko fseek
#  define ftello ftell
   typedef long _off_t;
#  define _off_t off_t
#endif
*/

/* Enable POSIX extensions if present */
#cmakedefine _XOPEN_SOURCE @_XOPEN_SOURCE@

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned char', `unsigned short', `unsigned int' or `unsigned
   long' according with size of `sin_port' in `struct sockaddr_in', if
   <sys/types.h>, <sys/socket.h> or <netinet/in.h> does not define
   `in_port_t'. */
#cmakedefine IN_PORT_T_REPLACEMENT 1
#ifdef IN_PORT_T_REPLACEMENT
#  define in_port_t @IN_PORT_T_REPLACEMENT@
#endif

#cmakedefine SOCKLEN_T_REPLACEMENT 1
#ifdef SOCKLEN_T_REPLACEMENT
#  define socklen_t @SOCKLEN_T_REPLACEMENT@
#endif

#cmakedefine SSIZE_T_REPLACEMENT 1
#ifdef SSIZE_T_REPLACEMENT
#  define ssize_t @SSIZE_T_REPLACEMENT@
#endif

#cmakedefine HAVE_GMTIME_R @HAVE_GMTIME_R@

#cmakedefine HAVE_ATTRIBUTE_PURE
#ifdef HAVE_ATTRIBUTE_PURE
#  define PURE_FUNCTION __attribute__((pure))
#else
#  define PURE_FUNCTION const
#endif

#ifdef _MSC_VER
#  define NORETURN __declspec(noreturn)
#else
#  define NORETURN __attribute__((noreturn))
#endif

#ifdef _WIN32
//#  undef socket
//#  undef close_socket
//#  undef fdopen
//#  undef fdclose
#  define socket w32_socket
#  define close_socket(f) closesocket(f)
#  define fdopen w32_fdopen
#  define fdclose w32_fdclose
#  define tmpfile w32_tmpfile
#  include "win32.h"

#ifdef _MSC_VER
#define inline _inline
#define snprintf _snprintf
#define popen _popen
#define pclose _pclose
#define close _close
#define write _write
#define lseek _lseek
#define read _read
#define atoll _atoi64
#define ftruncate _chsize
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define access _access
#define getpid _getpid
#define isatty _isatty
#endif

#  define WIN32_LEAN_AND_MEAN

/* MinGW assumes we are compiling for Windows NT 4.0 but ws2tcpip.h
   defines getaddrinfo only for Windows XP and newer */
#cmakedefine HAVE_WSPIAPI_H 1

#  if defined(__MINGW32__) && !defined(HAVE_WSPIAPI_H)
#    if !defined(WINVER) || (WINVER < 0x0501)
#      define WINVER 0x0501
#    endif
#    if !defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0501)
#      define _WIN32_WINNT 0x0501
#    endif
#  endif
#endif // WIN32

#endif /* H_CONFIG */
