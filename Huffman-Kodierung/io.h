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
extern char input_filename[MAX_FILENAME_LENGTH];

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

/**
 * Liest aus einer Datei die maximale Blockgröße 
 * und schreibt den Inhalt in den in_puffer.
 * @return Gelesene Anzahl der Zeichen.
 */
extern size_t read_file();

/**
 * Schreibt den Inhalt des out_puffers in eine Datei 
 * bis verbleibende Blockgröße erreicht ist.
 * @return Geschriebene Anzahl der Zeichen.
 */
extern size_t write_file();

/**
 * Diese Funktion öffnet die Eingabedatei und initisiert
 * den Ausgabepuffer als leer.
 * @param in_filename Name der Eingabedatei.
 * @param in_stream Filestream der Eingabedatei.
 * @return Liefer einen Exit Code zurück SUCCESS_RUN, wenn öffen erflogreich
 *         war und IO_ERROR, falls das Öffnen Fehlerhaft war.
 */
extern EXIT_CODES open_infile(char *in_filename);

/**
 * Diese Funktion öffnet die Ausgabedatei und initisiert
 * den Eingabepuffer als leer.
 * @param out_filename Name der Ausgabedatei.
 * @param out_stream Filestream der Ausgabedatei.
 * @return Liefer einen Exit Code zurück SUCCESS_RUN, wenn öffen erflogreich
 *         war und IO_ERROR, falls das Öffnen Fehlerhaft war.
 */
extern EXIT_CODES open_outfile(char *out_filename);

/**
 * Diese Funktion schließt die Eingabedatei.
 * @return Liefer einen Exit Code zurück SUCCESS_RUN, wenn schließen erflogreich
 *         war und IO_ERROR, falls das Schließen Fehlerhaft war.
 */
extern EXIT_CODES close_infile();

/**
 * Diese Funktion schließt die Ausgabedatei. Beim Schließen der Ausgabedatei
 * muss der Inhalt des Ausgabepuffers vorher noch einmal in die Ausgabedatei
 * geschrieben werden.
 * @return Liefer einen Exit Code zurück SUCCESS_RUN, wenn schließen erflogreich
 *         war und IO_ERROR, falls das Schließen Fehlerhaft war.
 */
extern EXIT_CODES close_outfile();

/**
 * Zeigt Informationen über die Größe der Ein- und Ausgabedatei an
 * und die Programmlaufzeit in Sekunden.
 * @param in_filename Die Eingabedatei.
 * @param out_filename Die Ausgabedatei.
 * @param prg_start Der Startzeitpunkt des Programms.
 * @param prg_end Der Endzeitpunkt des Programms.
 */
extern void showInfo(char *in_filename, char *out_filename, clock_t prg_start, clock_t prg_end);


#endif

