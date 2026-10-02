/*
 * The Spread Toolkit.
 *     
 * The contents of this file are subject to the Spread Open-Source
 * License, Version 1.0 (the ``License''); you may not use
 * this file except in compliance with the License.  You may obtain a
 * copy of the License at:
 *
 * http://www.spread.org/license/
 *
 * or in the file ``license.txt'' found in this distribution.
 *
 * Software distributed under the License is distributed on an AS IS basis, 
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License 
 * for the specific language governing rights and limitations under the 
 * License.
 *
 * The Creators of Spread are:
 *  Yair Amir, Michal Miskin-Amir, Jonathan Stanton, John Schultz.
 *
 *  Copyright (C) 1993-2016 Spread Concepts LLC <info@spreadconcepts.com>
 *
 *  All Rights Reserved.
 *
 * Major Contributor(s):
 * ---------------
 *    Amy Babay            babay@cs.jhu.edu - accelerated ring protocol.
 *    Ryan Caudy           rcaudy@gmail.com - contributions to process groups.
 *    Claudiu Danilov      claudiu@acm.org - scalable wide area support.
 *    Cristina Nita-Rotaru crisn@cs.purdue.edu - group communication security.
 *    Theo Schlossnagle    jesus@omniti.com - Perl, autoconf, old skiplist.
 *    Dan Schoenblum       dansch@cnds.jhu.edu - Java interface.
 *
 */

#ifndef INC_ARCH
#define INC_ARCH

/*
 * Each record in this file represents an architecture.
 * Each record contains the following fields:
 *
 *      #define         INTSIZE{16,32,64}
 *      #define         ARCH_SCATTER_{CONTROL,ACCRIGHTS,NONE}
 *      #define         ARCH_ENDIAN{0x00000000,0x80000080}
 *      #define         LOC_INLINE { __inline__ or blank }
 *      #define         ARCH_SCATTER_SIZE { sys dependent variable }
 *      #define         HAVE_GOOD_VARGS ( exists if true )
 *      #define         HAVE_LRAND48 ( exists if true )
 *      #define         HAVE_STDINT_H   ( exists if true --currently glibc2.1 needs it )
 *      typedef         {sys dependent type} sockopt_len_t;
 *      #define         ERR_TIMEDOUT    EAGAIN
 *      #define         sock_errno 
 *      #define         sock_strerror 
 *      #define         sock_set_errno(a) (errno = (a)) 
 */

#undef          INTSIZE32
#undef          INTSIZE64
#undef          INTSIZE16


/* If we aren't using windows... we can use autoconf */

#  include "config.h"

#if defined(__BYTE_ORDER__) && \
    (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#  define ARCH_ENDIAN 0x00000000
#else
#  define ARCH_ENDIAN 0x80000080
#endif

  
#  define LOC_INLINE __inline__
  
#  ifndef __GNUC__
#    define __inline__ inline
#  endif

/* Need to add special cases, SUNOS gets 64, IRIX gets 512 */  
#  ifdef MSG_MAXIOVLEN
#    define ARCH_SCATTER_SIZE MSG_MAXIOVLEN
#  else
#    define ARCH_SCATTER_SIZE 1024
#  endif

#  define HAVE_GOOD_VARGS
  
#  ifndef ERR_TIMEDOUT
#    define ERR_TIMEDOUT ETIMEDOUT
#  endif
  
#  ifndef RAND_MAX
#    define RAND_MAX 2147483647
#  endif
  
#  define sock_errno        errno
#  define sock_strerror     strerror
#  define sock_set_errno(a) (errno = (a)) 
  
#  ifndef byte
#    define byte u_int8_t
#  endif

#  ifndef int16
#    define int16 int16_t
#  endif

#  ifndef int16u
#    define int16u u_int16_t
#  endif

#  ifndef int32
#    define int32 int32_t
#  endif

#  ifndef int32u
#    define int32u u_int32_t
#  endif

#  ifndef INVALID_SOCKET
#    define INVALID_SOCKET (-1)
#  elif INVALID_SOCKET != -1
#    error "INVALID_SOCKET must be -1!"
#  endif
  

/* Pick which rand version to use */
#ifdef HAVE_LRAND48
#  define get_rand lrand48
#else
#  define get_rand rand
#endif

/* Useful CPP macros to make strings from #defines */  
#define Q(x)    # x
#define QQ(x)   Q(x)

#define         ENDIAN_TYPE             0x80000080

#define         Get_endian( t )      ( (t) &  ENDIAN_TYPE )
#define         Set_endian( t )      ( ( (t) & ~ENDIAN_TYPE ) | ARCH_ENDIAN )
#define         Same_endian( t )     ( ( (t) & ENDIAN_TYPE ) == ARCH_ENDIAN )
#define         Clear_endian( t )    ( (t) & ~ENDIAN_TYPE )

#ifndef         Flip_int16
#  define       Flip_int16( t )      ( ( ((t) >> 8) & 0x00ff) | ( ((t) << 8) & 0xff00) )
#endif

#ifndef         Flip_int32
#  define       Flip_int32( t )      ( ( ((t) >> 24) & 0x000000ff) | ( ((t) >> 8) & 0x0000ff00) | ( ((t) << 8) & 0x00ff0000) | ( ((t) << 24) & 0xff000000) )
#endif

#ifndef         Flip_int64
#  define       Flip_int64( t ) ( \
  (((t) & ((int64_t) 0xff <<  0)) << 56) | (((t) & ((int64_t) 0xff <<  8)) << 40) | \
  (((t) & ((int64_t) 0xff << 16)) << 24) | (((t) & ((int64_t) 0xff << 24)) <<  8) | \
  (((t) & ((int64_t) 0xff << 32)) >>  8) | (((t) & ((int64_t) 0xff << 40)) >> 24) | \
  (((t) & ((int64_t) 0xff << 48)) >> 40) | (((t) & ((int64_t) 0xff << 56)) >> 56) )
#endif
 

#define         channel                 int
#define         mailbox                 int

typedef struct  dummy_membership_id {
        int32   proc_id;
        int32   time;
} membership_id;

typedef struct  dummy_group_id {
        membership_id   memb_id;
        int32           index;
} group_id;

/* 
 * General Useful Types
 */

#ifndef __cplusplus
/*
 * May want to just undef it as shown below. Test to see what we want. 
 * work around bad/different bool definitions in system headers
 * #undef bool     
 */
typedef         int           bool;
#endif

#ifndef TRUE
#  define         TRUE            1
#endif

#ifndef FALSE
#  define         FALSE           0
#endif

#endif  /* INC_ARCH */
