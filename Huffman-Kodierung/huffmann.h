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

#endif /* HUFFMANN_H */

