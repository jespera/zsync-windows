project(zsync C)

cmake_minimum_required(VERSION 2.8)

set(PACKAGE_BUGREPORT "http://zsync.moria.org.uk/")
set(PACKAGE_NAME "zsync")
set(PACKAGE_VERSION "0.6.2")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}")
set(PACKAGE "${PACKAGE_NAME}")
set(PACKAGE_URL "")
set(VERSION "${PACKAGE_VERSION}")

include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckIncludeFile)
include(CheckTypeSize)

set(CMAKE_MODULE_PATH ${zsync_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

include_directories(${zsync_BINARY_DIR} ${DMALLOC_INCLUDE_DIR})

add_definitions(-DHAVE_CONFIG_H)
if(CMAKE_COMPILER_IS_GNUCC)
  set(ZSCFLAGS ${ZSCFLAGS} -D_BSD_SOURCE=1 -D_XOPEN_SOURCE=600 -ffast-math -Wall -Wwrite-strings -Winline -Wextra -Winline -Wmissing-noreturn -Wredundant-decls -Wnested-externs -Wundef -Wbad-function-cast -Wcast-align -Wvolatile-register-var)
  set(CMAKE_C_FLAGS "-W -Wall -Wshadow")
  set(CMAKE_CXX_FLAGS "-W -Wall -Wshadow")
endif(CMAKE_COMPILER_IS_GNUCC)

option(WITH_DMALLOC "Use the dmalloc debugging malloc package" OFF)
option(WITH_LARGE_FILE_SUPPORT "Enable support for files > 2 GiB on 32-bit platforms. Do not disable unless you know very well what you are doing." ON)


add_definitions(${ZSCFLAGS})
set(CMAKE_REQUIRED_DEFINITIONS ${ZSCFLAGS})

message(STATUS "ZSCFLAGS = ${ZSCFLAGS}")

if(WIN32)
  #set(SOCKET_LIBRARY ws2_32) # Winsock 2 -- wsock32??? (that's Winsock 1.1, but it's what configure.ac said for mingw32?
#  find_library(SOCKET_LIBRARY ws2_32)
  set(SOCKET_LIBRARY ${SOCKET_LIBRARY} ws2_32) # Why is this necessary on MinGW!?
elseif(CMAKE_SYSTEM_NAME MATCHES "(Solaris|SunOS)" )
  find_library(SOCKET_LIBRARY socket)
endif(WIN32)

set(CMAKE_REQUIRED_LIBRARIES ${SOCKET_LIBRARY})

if(MSVC)
  check_function_exists(_fseeki64 HAVE_FSEEKO)
  if(HAVE_FSEEKO)
    set(FSEEKO_REPLACEMENT _fseeki64)
  endif(HAVE_FSEEKO)
else(MSVC)
  check_function_exists(fseeko HAVE_FSEEKO)
endif(MSVC)

if(WIN32)
  check_symbol_exists(gmtime_r time.h HAVE_GMTIME_R)
  check_include_file(wspiapi.h HAVE_WSPIAPI_H)
  if (NOT HAVE_WSPIAPI_H)
    message(STATUS "WARNING: Without wspiapi.h, this build will only work on Windows XP and newer versions")
  endif (NOT HAVE_WSPIAPI_H)
  check_include_file(ws2tcpip.h HAVE_WS2TCPIP_H)
  if (HAVE_WSPIAPI_H OR HAVE_WS2TCPIP_H)
    set(HAVE_GETADDRINFO TRUE)
    if(CMAKE_COMPILER_IS_GNUCC AND NOT HAVE_WSPIAPI) # MinGW version that does not yet provide wspiapi.h (no MinGW provides wspiapi.h so far, but just in case in the future they do)
      add_definitions("-DWINVER=0x501") # MinGW assumes we are compiling for Windows NT 4.0 but in ws2tcpip.h defines getaddrinfo only for Windows XP and newer
    endif(CMAKE_COMPILER_IS_GNUCC AND NOT HAVE_WSPIAPI)
  endif (HAVE_WSPIAPI_H OR HAVE_WS2TCPIP_H)
else(WIN32)
  check_function_exists(getaddrinfo HAVE_GETADDRINFO)
endif(WIN32)

check_include_file(inttypes.h HAVE_INTTYPES_H)

find_library(LIBSOCKET_FOUND socket)
if(LIBSOCKET_FOUND)
  set(HAVE_LIBSOCKET 1)
endif(LIBSOCKET_FOUND)

check_function_exists(memcpy HAVE_MEMCPY)
check_function_exists(mkstemp HAVE_MKSTEMP)
check_function_exists(pread HAVE_PREAD)
check_function_exists(pwrite HAVE_WRITE)

check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(dmalloc.h WITH_DMALLOC)

check_type_size(off_t SIZEOF_OFF_T)
#if(WIN32 AND SIZEOF_OFF_T EQUAL 4)
#  set(
#endif(WIN32 SIZEOF_OFF_T EQUAL 4)

check_type_size(size_t SIZEOF_SIZE_T)
if(NOT HAVE_SIZEOF_SIZE_T)
  set(SIZE_T_REPLACEMENT "unsigned int")
endif(NOT HAVE_SIZEOF_SIZE_T)

set(CMAKE_EXTRA_INCLUDE_FILES sys/socket.h sys/types.h)
check_type_size(socklen_t SIZEOF_SOCKLEN_T)
if(NOT HAVE_SIZEOF_SOCKLEN_T)
  set(SOCKLEN_T_REPLACEMENT "int")
endif(NOT HAVE_SIZEOF_SOCKLEN_T)
set(CMAKE_EXTRA_INCLUDE_FILES )

# Define to `unsigned char', `unsigned short', `unsigned int' or `unsigned
#   long' according with size of `sin_port' in `struct sockaddr_in', if
#   <sys/types.h>, <sys/socket.h> or <netinet/in.h> does not define
#   `in_port_t'. */
check_include_file(sys/socket.h HAVE_SOCKET_H)
if(HAVE_SOCKET_H)
  set(SOCKET_H sys/socket.h)
endif(HAVE_SOCKET_H)

check_include_file(netinet/in.h HAVE_NETINET_IN_H)
if(HAVE_NETINET_IN_H)
  set(NETINET_IN_H netinet/in.h)
endif(HAVE_NETINET_IN_H)

set(CMAKE_EXTRA_INCLUDE_FILES sys/types.h ${SOCKET_H} ${NETINET_IN_H})
check_type_size(in_port_t SIZEOF_IN_PORT_T)
if(NOT HAVE_SIZEOF_IN_PORT_T)
  check_type_size("unsigned char" SIZEOF_UNSIGNED_CHAR)
  check_type_size("unsigned short" SIZEOF_UNSIGNED_SHORT)
  check_type_size("unsigned int" SIZEOF_UNSIGNED_INT)
  check_type_size("unsigned long" SIZEOF_UNSIGNED_LONG)
  try_run(SIZEOF_IN_PORT_T_RUN_RESULT SIZEOF_IN_PORT_T_COMPILE_RESULT
          ${zsync_BINARY_DIR}/cmake ${zsync_SOURCE_DIR}/cmake/in_port_t_size.c
          RUN_OUTPUT_VARIABLE SIZEOF_IN_PORT_T_RUN_OUTPUT)
  if(SIZEOF_IN_PORT_T_RUN_OUTPUT EQUAL SIZEOF_UNSIGNED_CHAR)
      set(IN_PORT_T_REPLACEMENT "unsigned char")
  elseif(SIZEOF_IN_PORT_T_RUN_OUTPUT EQUAL SIZEOF_UNSIGNED_SHORT)
      set(IN_PORT_T_REPLACEMENT "unsigned short")
  elseif(SIZEOF_IN_PORT_T_RUN_OUTPUT EQUAL SIZEOF_UNSIGNED_INT)
      set(IN_PORT_T_REPLACEMENT "unsigned int")
  elseif(SIZEOF_IN_PORT_T_RUN_OUTPUT EQUAL SIZEOF_UNSIGNED_LONG)
      set(IN_PORT_T_REPLACEMENT "unsigned long")
  endif(SIZEOF_IN_PORT_T_RUN_OUTPUT EQUAL SIZEOF_UNSIGNED_CHAR)
endif(NOT HAVE_SIZEOF_IN_PORT_T)


# TODO
#Define to 1 if `h_errno' is declared by <netdb.h> */
#undef H_ERRNO_DECLARED

if(WITH_LARGE_FILE_SUPPORT)
  include(CheckLargeFileSupport)
  check_large_file_support()
endif(WITH_LARGE_FILE_SUPPORT)

if(NOT MSVC)
  set(_XOPEN_SOURCE 600) # Enable POSIX extensions if present
  set(BSD_SOURCE 1)
endif(NOT MSVC)

#/* Define to empty if `const' does not conform to ANSI C. */
##undef const

configure_file(config.h.cmake ${zsync_BINARY_DIR}/config.h)

if(NOT WIN32)
  find_library(MATH_LIBRARY m)
endif(NOT WIN32)

add_subdirectory(librcksum)
add_subdirectory(zlib)
add_subdirectory(libzsync)
#add_subdirectory(doc)

include_directories(librcksum zlib libzsync ${zsync_SOURCE_DIR})

if(WIN32)
  set(WIN32_SOURCES win32.h win32.c)
endif(WIN32)

add_executable(zsyncmake make.c makegz.c makegz.h format_string.h ${WIN32_SOURCES})
target_link_libraries(zsyncmake zsynclib ${SOCKET_LIBRARY} rcksum inflate deflate zsynclib ${MATH_LIBRARY} ${DMALLOC_LIBRARIES})

if(NOT HAVE_GETADDRINFO)
  set(GETTADDRINFO_SOURCES getaddrinfo.h getaddrinfo.c)
endif(NOT HAVE_GETADDRINFO)

add_executable(zsync client.c http.c http.h url.c url.h progress.c progress.h base64.c format_string.h zsglobal.h ${GETADDRINFO_SOURCES} ${WIN32_SOURCES})
target_link_libraries(zsync zsynclib ${SOCKET_LIBRARY} rcksum inflate deflate zsynclib ${MATH_LIBRARY} ${DMALLOC_LIBRARIES})

# TODO
# install(FILES COPYING README INSTALL check-zsyncmake)
