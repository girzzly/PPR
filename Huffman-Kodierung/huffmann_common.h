/** 
 * @file huffmann_common.h
 * 
 * In diesem Modul...
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#ifndef _HUFFMANN_COMMON_H
#define _HUFFMANN_COMMON_H

#define DPRINT(P) printf("%d", (P) )

#define CPRINT(P) printf("%c", (P) )

#define XPRINT(P) printf("%x", (P) )

#define DPRINTLN(P) printf("%d\n", (P) )

#define CPRINTLN(P) printf("%c\n", (P) )

#define XPRINTLN(P) printf("%x\n", (P) )

/** Bitrepräsentierung. */
typedef enum
{
    OFF,
    ON
} BIT;

#endif

