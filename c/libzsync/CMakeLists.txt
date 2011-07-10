project(libzsync C)

include_directories(${zsync_SOURCE_DIR} ${zsync_BINARY_DIR})

add_definitions(${ZSCFLAGS})

add_library(zsynclib STATIC zmap.h zsync.h sha1.h zsync.c zmap.c sha1.c)
add_executable(sha1test sha1.h sha1.c sha1test.c)

#TODO
#install(targets zsynclib ...)

