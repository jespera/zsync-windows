project(zsynczlib)

include_directories(${zsync_SOURCE_DIR} ${zsync_BINARY_DIR})

add_definitions(${ZSCFLAGS})

add_library(inflate zlib.h inflate.c inflate.h inffixed.h adler32.c inftrees.c inftrees.h zutil.c zutil.h crc32.c crc32.h zconf.h)

add_library(deflate deflate.c deflate.h compress.c trees.c trees.h)

# TODO
#install(files README.zsync)
