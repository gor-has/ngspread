#ifndef SPU_CONFIG_H
#define SPU_CONFIG_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define HAVE_ARPA_INET_H 1
#define HAVE_ASSERT_H 1
#define HAVE_ERRNO_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIMITS_H 1
#define HAVE_NETDB_H 1
#define HAVE_NETINET_IN_H 1
#define HAVE_POLL_H 1
#define HAVE_PTHREAD_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_STRINGS_H 1
#define HAVE_SYS_SOCKET_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_UNISTD_H 1

#define HAVE_INTXX_T 1
#define HAVE_U_INTXX_T 1
#define HAVE_UINTXX_T 1
#define HAVE_INT64_T 1
#define HAVE_U_INT64_T 1
#define HAVE_SOCKLEN_T 1
#define HAVE_SIZE_T 1
#define HAVE_SSIZE_T 1
#define HAVE_CLOCK_T 1
#define HAVE_PID_T 1

#define HAVE_MEMMOVE 1
#define HAVE_SNPRINTF 1
#define HAVE_STRERROR 1
#define HAVE_TIME 1
#define HAVE_GETTIMEOFDAY 1
#define HAVE_CLOCK_GETTIME_CLOCK_MONOTONIC 1

#define SIZEOF_CHAR 1
#define SIZEOF_SHORT_INT 2
#define SIZEOF_INT 4
#define SIZEOF_LONG_INT 8
#define SIZEOF_LONG_LONG_INT 8

#endif
