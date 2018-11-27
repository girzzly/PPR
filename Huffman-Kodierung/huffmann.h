/**  
 * @file huffmann.h
 * 
 * In diesem Modul...
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include "io.h"

#ifndef _HUFFMANN_H
#define _HUFFMANN_H

/**
 * Kopiert den Eingabepuffer byteweise in den Ausgabepuffer.
 * @param in Das zu kopierende Array.
 * @param out Das fertig kopierte Array.
 */
extern void copy_chars(char in[], char out[]);

/**
 * Kopiert den EIngabepuffer bitweise in den Ausgabepuffer.
 * @param in Das zu kopierende Array.
 * @param out Das fertig kopierte Array.
 */
extern void copy_bits(char in[], char out[]);


#endif /* HUFFMANN_H */

