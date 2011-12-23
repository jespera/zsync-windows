project(librcksum C)

include_directories(${zsync_SOURCE_DIR} ${zsync_BINARY_DIR})

add_definitions(${ZSCFLAGS} -DHAVE_CONFIG_H)

set(rcksum_SRCS internal.h rcksum.h md4.h rsum.c hash.c state.c range.c md4.c)

if(MSVC)
  set_source_files_properties(${rcksum_SRCS} PROPERTIES LANGUAGE CXX)
endif(MSVC)

add_library(rcksum STATIC ${rcksum_SRCS})
add_executable(md4test md4test.c)
target_link_libraries(md4test rcksum)

# TODO
# install(targets rcksum ...)
