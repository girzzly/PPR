/** 
 * @file io.h
 * 
 * In diesem Modul... 
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include <stdbool.h>

#include "huffmann_common.h"

#ifndef _IO_H
#define _IO_H

/** 
 * Dieses Makro gibt ein Bit aus einem �bergebenen Byte
 * an einer bestimmten Position wieder. 
 */
#define GET_BIT(BYTE, POS) ( ( (BYTE) & ( 0x80 >> (POS) ) ) >> ( 7 - (POS) ) )

/** 
 * Dieses Makro setzt ein Bit an einer bestimmten
 * Position eines �bergebnenen Byte.
 */
#define PUT_BIT(BYTE, BIT, POS) ( (BIT) == ON ) \
                                   ? (BYTE) | ( 0x80 >> (POS) ) \
                                   : (BYTE) & ~( 0x80 >> (POS) )

/** Maximale Puffergr��e. */
#define BUF_SIZE 4096

/** Index f�r den in_puffer. */
extern int index_byte;

/** Index f�r den out_puffer. */
extern int index_bit;
/** Position des Bits im Byte. */
extern int position_bit;

/** F�llstand f�r den in_puffer. */
extern int fill_level_in_puffer;
/** F�llstand f�r den out_puffer. */
extern int fill_level_out_puffer;

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
 * Setzt die Puffer und golaben Variabeln zur�ck.
 */
extern void reset(void);

#endif

