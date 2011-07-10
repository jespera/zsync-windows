project(librcksum C)

include_directories(${zsync_SOURCE_DIR} ${zsync_BINARY_DIR})

add_definitions(${ZSCFLAGS})

add_library(rcksum STATIC internal.h rcksum.h md4.h rsum.c hash.c state.c range.c md4.c)
add_executable(md4test md4test.c)
target_link_libraries(md4test rcksum)

# TODO
# install(targets rcksum ...)
