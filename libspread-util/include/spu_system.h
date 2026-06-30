

#ifndef SPU_SYSTEM_H
#define SPU_SYSTEM_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>

#define SPU_HAVE_INT64_T 1
#define SPU_HAVE_INTTYPES_H 1
#define SPU_HAVE_INTXX_T 1
#define SPU_HAVE_LIMITS_H 1
#define SPU_HAVE_STDLIB_H 1
#define SPU_HAVE_U_INT 1
#define SPU_HAVE_U_INT64_T 1
#define SPU_HAVE_U_INTXX_T 1

#define SPU_SIZEOF_CHAR 1
#define SPU_SIZEOF_SHORT_INT 2
#define SPU_SIZEOF_INT 4
#define SPU_SIZEOF_LONG_INT 8
#define SPU_SIZEOF_LONG_LONG_INT 8

#include "spu_system_defs.h"

#endif
