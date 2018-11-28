/** 
 * @file io.c
 * 
 * Das Modul io stellt die Funktionen zum byte- und bitweisen Lesen
 * und Schreiben zur Verfügung.
 * 
 * @author Dominik
 *
 * @date 2018-11-06
 */

#include <stdbool.h>
#include <string.h>

#include "huffmann_common.h"
#include "io.h"

/** 
 * Dieses Makro gibt ein Bit aus einem übergebenen Byte
 * an einer bestimmten Position wieder. 
 */
#define GET_BIT(BYTE, POS) ( ( (BYTE) & ( 0x80 >> (POS) ) ) >> ( 7 - (POS) ) )

/** 
 * Dieses Makro setzt ein Bit an einer bestimmten
 * Position eines übergebnenen Byte.
 */
#define PUT_BIT(BYTE, BIT, POS) ( (BIT) == ON ) \
                                   ? (BYTE) | ( 0x80 >> (POS) ) \
                                   : (BYTE) & ~( 0x80 >> (POS) )

/** 
 * Konstante für die Größe eines Bytes.
 */
#define BYTE_SIZE 8


/** Index für den in_puffer. */
static int index_byte;

/** Index für den out_puffer. */
static int index_bit;
/** Position des Bits im Byte. */
static int position_bit;

/** Füllstand für den in_puffer. */
static int fill_level_in_puffer;
/** Füllstand für den out_puffer. */
static int fill_level_out_puffer;


/** Bytespeicher. */
static unsigned char in_puffer[BUF_SIZE];

/** Bitspeicher. */
static unsigned char out_puffer[BUF_SIZE];


extern bool has_next_char(void)
{
    return index_byte < fill_level_in_puffer;
}

extern unsigned char read_char(void)
{
    return in_puffer[index_byte];
}

extern void write_char(unsigned char c)
{
    out_puffer[index_byte] = c;
    index_byte++;
    fill_level_out_puffer++;
}

extern bool has_next_bit(void)
{
    return (index_bit < fill_level_in_puffer) && (position_bit < BYTE_SIZE);
}

extern BIT read_bit(void)
{   
    return GET_BIT(in_puffer[index_bit], position_bit);
}

extern void write_bit(BIT c)
{    
    out_puffer[index_bit] = PUT_BIT(out_puffer[index_bit], c, position_bit);
    
    position_bit++;
    
    if(position_bit >= BYTE_SIZE)
    {
        position_bit = 0;
        index_bit++;
    }
    
    fill_level_out_puffer = index_bit;
}

static void reset(void)
{
    index_byte = 0;
    
    index_bit = 0;
    position_bit = 0;

    fill_level_out_puffer = 0;
    fill_level_in_puffer = 0;
}

extern void put_puffer_in(unsigned char in[])
{
    reset();
    
    fill_level_in_puffer = strlen((char*) in);
    strncpy((char*) in_puffer, (char*) in, fill_level_in_puffer);
}

extern void put_puffer_out(unsigned char out[])
{
    strncpy((char*) out, (char*) out_puffer, fill_level_out_puffer);
}