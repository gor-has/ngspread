

#ifndef STDARCH_AUTOCONF_H
#define STDARCH_AUTOCONF_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <limits.h>

typedef int8_t      stdarch_int8;
typedef uint8_t     stdarch_uint8;
typedef int16_t     stdarch_int16;
typedef uint16_t    stdarch_uint16;
typedef int32_t     stdarch_int32;
typedef uint32_t    stdarch_uint32;
typedef int64_t     stdarch_int64;
typedef uint64_t    stdarch_uint64;
typedef size_t      stdarch_size;
typedef ssize_t     stdarch_ssize;

#define STDARCH_MAX_BYTE_ALIGNMENT 8


#define STDENDIAN16_NET0_FROM_HOST 1
#define STDENDIAN16_NET1_FROM_HOST 0

#define STDENDIAN16_HOST0_FROM_NET 1
#define STDENDIAN16_HOST1_FROM_NET 0

#define STDENDIAN32_NET0_FROM_HOST 3
#define STDENDIAN32_NET1_FROM_HOST 2
#define STDENDIAN32_NET2_FROM_HOST 1
#define STDENDIAN32_NET3_FROM_HOST 0

#define STDENDIAN32_HOST0_FROM_NET 3
#define STDENDIAN32_HOST1_FROM_NET 2
#define STDENDIAN32_HOST2_FROM_NET 1
#define STDENDIAN32_HOST3_FROM_NET 0

#define STDENDIAN64_NET0_FROM_HOST 7
#define STDENDIAN64_NET1_FROM_HOST 6
#define STDENDIAN64_NET2_FROM_HOST 5
#define STDENDIAN64_NET3_FROM_HOST 4
#define STDENDIAN64_NET4_FROM_HOST 3
#define STDENDIAN64_NET5_FROM_HOST 2
#define STDENDIAN64_NET6_FROM_HOST 1
#define STDENDIAN64_NET7_FROM_HOST 0

#define STDENDIAN64_HOST0_FROM_NET 7
#define STDENDIAN64_HOST1_FROM_NET 6
#define STDENDIAN64_HOST2_FROM_NET 5
#define STDENDIAN64_HOST3_FROM_NET 4
#define STDENDIAN64_HOST4_FROM_NET 3
#define STDENDIAN64_HOST5_FROM_NET 2
#define STDENDIAN64_HOST6_FROM_NET 1
#define STDENDIAN64_HOST7_FROM_NET 0



/*
#define STD_HAVE_INT8_T      1
#define STD_HAVE_INT16_T     1
#define STD_HAVE_INT32_T     1
#define STD_HAVE_INT64_T     1

#define STD_HAVE_UINT8_T     1
#define STD_HAVE_UINT16_T    1
#define STD_HAVE_UINT32_T    1
#define STD_HAVE_UINT64_T    1

#define STD_HAVE_SIZE_T      1
#define STD_HAVE_SSIZE_T     1

#define STD_SIZEOF_CHAR          1
#define STD_SIZEOF_SHORT         2
#define STD_SIZEOF_INT           4
#define STD_SIZEOF_LONG          8
#define STD_SIZEOF_LONG_LONG     8
*/

#endif
