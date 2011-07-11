#cmakedefine HAVE_FSEEKO

#ifdef FSEEKO_REPLACEMENT
#  define fseeko @FSEEKO_REPLACEMENT@
#endif

/* Define to 1 if you have the `getaddrinfo' function. */
#cmakedefine HAVE_GETADDRINFO

/* Define to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H

/* Define to 1 if you have the `socket' library (-lsocket). */
#cmakedefine HAVE_LIBSOCKET

/* Define to 1 if you have the `memcpy' function. */
#cmakedefine HAVE_MEMCPY

/* Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H

/* Define to 1 if you have the `mkstemp' function. */
#cmakedefine HAVE_MKSTEMP

/* Define to 1 if you have the `pread' function. */
#cmakedefine HAVE_PREAD

/* Define to 1 if you have the `pwrite' function. */
#cmakedefine HAVE_PWRITE

/* Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H

/* Define to 1 if `h_errno' is declared by <netdb.h> */
#undef H_ERRNO_DECLARED

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

/* Define to 1 if you have the ANSI C header files. */
/* #undef STDC_HEADERS */

/* Version number of package */
#define VERSION "@VERSION@"

/* Define if using the dmalloc debugging malloc package */
#cmakedefine WITH_DMALLOC

/* Enable BSD extensions if present */
/* #undef _BSD_SOURCE */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Enable POSIX extensions if present */
/* #undef _XOPEN_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned char', `unsigned short', `unsigned int' or `unsigned
   long' according with size of `sin_port' in `struct sockaddr_in', if
   <sys/types.h>, <sys/socket.h> or <netinet/in.h> does not define
   `in_port_t'. */
#cmakedefine IN_PORT_T_REPLACEMENT
#ifdef IN_PORT_T_REPLACEMENT
#  define in_port_t @IN_PORT_T_REPLACEMENT@
#endif

#cmakedefine SIZE_T_REPLACEMENT
#ifdef SIZE_T_REPLACEMENT
#  define size_t @SIZE_T_REPLACEMENT@
#endif

#cmakedefine SOCKLEN_T_REPLACEMENT
#ifdef SOCKLEN_T_REPLACEMENT
#  define socklen_t @SOCKLEN_T_REPLACEMENT@
#endif
