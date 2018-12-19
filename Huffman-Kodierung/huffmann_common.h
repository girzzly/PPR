/** 
 * @file huffmann_common.h
 * 
 * Das Modul huffman_common fasst alle Definitionen, 
 * die von allen Modulen gemeinsam verwendet werden sollen, zusammen.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#ifndef _HUFFMANN_COMMON_H
#define _HUFFMANN_COMMON_H

/** Debug-Ausgabe für Dezimalzahlen. */
#define DPRINT(P) printf("%d", (P) )

/** Debug-Ausgabe für Zeichen. */
#define CPRINT(P) printf("%c", (P) )

/** Debug-Ausgabe für Hexzahlen. */
#define XPRINT(P) printf("%x", (P) )

/** Debug-Ausgabe für Dezimalzahlen mit Zeilenumbruch. */
#define DPRINTLN(P) printf("%d\n", (P) )

/** Debug-Ausgabe für Zeichen mit Zeilenumbruch. */
#define CPRINTLN(P) printf("%c\n", (P) )

/** Debug-Ausgabe für Hexzahlen mit Zeilenumbruch. */
#define XPRINTLN(P) printf("%x\n", (P) )

/** Zeilenumbruchsmakro. */
#define BR printf("\n")

/** Pufferausgabemarko. */
#define PRINT_PUFFER(PUFFER, SIZE) { int i; \
                         for (i = 0; i < (SIZE); i++) \
                            { CPRINT((PUFFER[i])); } BR; }

/** Bitrepräsentierung. */
typedef enum
{
    OFF,
    ON
} BIT;

/** Programm Exit-Codes. */
typedef enum
{
    SUCCESS_RUN,
    UNKNOWN_ERROR,
    ARGUMENTS_ERROR,
    IO_ERROR,
    COMPRESS_DECOMPRESS_ERROR
} EXIT_CODES;

#endif

