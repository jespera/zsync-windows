#ifndef PACK_H
#define PACK_H

#ifdef _MSC_VER
#  define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
#  define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#endif
