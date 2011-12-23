project(libzsync C)

include_directories(${zsync_SOURCE_DIR} ${zsync_BINARY_DIR})

add_definitions(${ZSCFLAGS} -DHAVE_CONFIG_H)

set(zsynclib_SRCS zmap.h zsync.h sha1.h zsync.c zmap.c sha1.c)
if(MSVC)
  set_source_files_properties(${zsynclib_SRCS} PROPERTIES LANGUAGE CXX)
endif(MSVC)
add_library(zsynclib STATIC ${zsynclib_SRCS})

add_executable(sha1test sha1.h sha1.c sha1test.c)

#TODO
#install(targets zsynclib ...)

