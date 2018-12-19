/**  
 * @file huffmann.h
 * 
 * Im Modul huffman wird die Komprimierung und Dekomprimierung realisiert.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include "io.h"

#ifndef _HUFFMANN_H
#define _HUFFMANN_H

/**
 * Diese Funktion öffnet die Ein- und Ausgabedatei und 
 * kopiert dann den Inhalt der Eingabedatei byteweise (compress)
 * in die Ausgabedatei. Am Ende werden beide Dateien geschlossen.
 * @param in_filename Filename der Eingabedatei.
 * @param out_filename Filename der Ausagbedatei.
 */
extern void compress(char in_filename[], char out_filename[]);

/**
 * Diese Funktion öffnet die Ein- und Ausgabedatei und 
 * kopiert dann den Inhalt der Eingabedatei bitweise (decompress)
 * in die Ausgabedatei. Am Ende werden beide Dateien geschlossen.
 * @param in_filename Filename der Eingabedatei.
 * @param out_filename Filename der Ausagbedatei.
 */
extern void decompress(char in_filename[], char out_filename[]);

/**
 * Kopiert den Eingabepuffer byteweise in den Ausgabepuffer.
 * @param in Das zu kopierende Array.
 * @param out Das fertig kopierte Array.
 */
//extern void copy_chars(char in[], char out[]);

/**
 * Kopiert den EIngabepuffer bitweise in den Ausgabepuffer.
 * @param in Das zu kopierende Array.
 * @param out Das fertig kopierte Array.
 */
//extern void copy_bits(char in[], char out[]);


#endif /* HUFFMANN_H */

