/** 
 * @file io.h
 * 
 * Das Modul io stellt die Funktionen zum byte- und bitweisen Lesen
 * und Schreiben zur Verfügung.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include <stdbool.h>

#include "huffmann_common.h"

#ifndef _IO_H
#define _IO_H

/** Maximale Puffergröße. */
#define BUF_SIZE 4096

/** Maximale Dateinamenlänge. */
#define MAX_FILENAME_LENGTH 256

/** Name der Input-Datei. */
extern char *input_filename;

/** Name der Output-Datei. */
extern char output_filename[MAX_FILENAME_LENGTH];

/**
 * Gibt an ob noch weitere Bytes aus dem Eingabepuffer gelesen werden können.
 * @return true falls nächstes Byte vorhanden,
 *         false falls nächstes Byte nicht vorhanden.
 */
extern bool has_next_char(void);

/**
 * Liefert mit jedem Aufruf das nächste Byte aus dem Eingabepuffer.
 * (Wird nur aufgerufen, wenn noch ein weiteres Byte vorhanden ist.)
 * @return Das zu lesende Byte.
 */
extern unsigned char read_char(void);

/**
 * Schreibt ein Byte an die nächste freie Position in den Ausgabepuffer.
 * @param c Das zu schreibende Byte.
 */
extern void write_char(unsigned char c);

/**
 * Gibt an, ob noch weitere Bits aus dem Eingabepuffer gelesen werden können.
 * @return true falls nächstes Bit vorhanden,
 *         false falls nächstes Bit nicht vorhanden.
 */
extern bool has_next_bit(void);

/**
 * Liefert mit jedem Aufruf das nächste Bit aus dem Eingabepuffer.
 * (Wird nur aufgerufen, wenn noch ein weiteres Bit vorhanden ist.)
 * @return Das zu lesende Bit.
 */
extern BIT read_bit(void);

/**
 * Schreibt ein Bit an die nächste freie Position in den Ausgabepuffer.
 * @param c Das zu schreibende Bit.
 */
extern void write_bit(BIT c);

#endif

