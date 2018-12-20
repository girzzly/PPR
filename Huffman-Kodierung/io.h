/** 
 * @file io.h
 * 
 * Das Modul io stellt die Funktionen zum byte- und bitweisen Lesen
 * und Schreiben zur Verf�gung.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include <stdbool.h>

#include "huffmann_common.h"

#ifndef _IO_H
#define _IO_H

/** Maximale Puffergr��e. */
#define BUF_SIZE 4096

/** Maximale Dateinamenl�nge. */
#define MAX_FILENAME_LENGTH 256

/** Name der Input-Datei. */
extern char input_filename[MAX_FILENAME_LENGTH];

/** Name der Output-Datei. */
extern char output_filename[MAX_FILENAME_LENGTH];

/**
 * Gibt an ob noch weitere Bytes aus dem Eingabepuffer gelesen werden k�nnen.
 * @return true falls n�chstes Byte vorhanden,
 *         false falls n�chstes Byte nicht vorhanden.
 */
extern bool has_next_char(void);

/**
 * Liefert mit jedem Aufruf das n�chste Byte aus dem Eingabepuffer.
 * (Wird nur aufgerufen, wenn noch ein weiteres Byte vorhanden ist.)
 * @return Das zu lesende Byte.
 */
extern unsigned char read_char(void);

/**
 * Schreibt ein Byte an die n�chste freie Position in den Ausgabepuffer.
 * @param c Das zu schreibende Byte.
 */
extern void write_char(unsigned char c);

/**
 * Gibt an, ob noch weitere Bits aus dem Eingabepuffer gelesen werden k�nnen.
 * @return true falls n�chstes Bit vorhanden,
 *         false falls n�chstes Bit nicht vorhanden.
 */
extern bool has_next_bit(void);

/**
 * Liefert mit jedem Aufruf das n�chste Bit aus dem Eingabepuffer.
 * (Wird nur aufgerufen, wenn noch ein weiteres Bit vorhanden ist.)
 * @return Das zu lesende Bit.
 */
extern BIT read_bit(void);

/**
 * Schreibt ein Bit an die n�chste freie Position in den Ausgabepuffer.
 * @param c Das zu schreibende Bit.
 */
extern void write_bit(BIT c);

/**
 * Liest aus einer Datei die maximale Blockgr��e 
 * und schreibt den Inhalt in den in_puffer.
 * @return Gelesene Anzahl der Zeichen.
 */
extern size_t read_file();

/**
 * Schreibt den Inhalt des out_puffers in eine Datei 
 * bis verbleibende Blockgr��e erreicht ist.
 * @return Geschriebene Anzahl der Zeichen.
 */
extern size_t write_file();

/**
 * Diese Funktion �ffnet die Eingabedatei und initisiert
 * den Ausgabepuffer als leer.
 * @param in_filename Name der Eingabedatei.
 * @param in_stream Filestream der Eingabedatei.
 * @return Liefer einen Exit Code zur�ck SUCCESS_RUN, wenn �ffen erflogreich
 *         war und IO_ERROR, falls das �ffnen Fehlerhaft war.
 */
extern EXIT_CODES open_infile(char *in_filename);

/**
 * Diese Funktion �ffnet die Ausgabedatei und initisiert
 * den Eingabepuffer als leer.
 * @param out_filename Name der Ausgabedatei.
 * @param out_stream Filestream der Ausgabedatei.
 * @return Liefer einen Exit Code zur�ck SUCCESS_RUN, wenn �ffen erflogreich
 *         war und IO_ERROR, falls das �ffnen Fehlerhaft war.
 */
extern EXIT_CODES open_outfile(char *out_filename);

/**
 * Diese Funktion schlie�t die Eingabedatei.
 * @return Liefer einen Exit Code zur�ck SUCCESS_RUN, wenn schlie�en erflogreich
 *         war und IO_ERROR, falls das Schlie�en Fehlerhaft war.
 */
extern EXIT_CODES close_infile();

/**
 * Diese Funktion schlie�t die Ausgabedatei. Beim Schlie�en der Ausgabedatei
 * muss der Inhalt des Ausgabepuffers vorher noch einmal in die Ausgabedatei
 * geschrieben werden.
 * @return Liefer einen Exit Code zur�ck SUCCESS_RUN, wenn schlie�en erflogreich
 *         war und IO_ERROR, falls das Schlie�en Fehlerhaft war.
 */
extern EXIT_CODES close_outfile();

/**
 * Zeigt Informationen �ber die Gr��e der Ein- und Ausgabedatei an
 * und die Programmlaufzeit in Sekunden.
 * @param in_filename Die Eingabedatei.
 * @param out_filename Die Ausgabedatei.
 * @param prg_start Der Startzeitpunkt des Programms.
 * @param prg_end Der Endzeitpunkt des Programms.
 */
extern void showInfo(char *in_filename, char *out_filename, clock_t prg_start, clock_t prg_end);


#endif

