/** 
 * @file io.c
 * 
 * In diesem Modul... 
 * 
 * @author Dominik
 *
 * @date 2018-11-06
 */

#include <stdbool.h>

#include "huffmann_common.h"
#include "io.h"


/** Index für den in_puffer. */
int index_byte = 0;

/** Index für den out_puffer. */
int index_bit = 0;
/** Position des Bits im Byte. */
int position_bit = 0;

/** Füllstand für den in_puffer. */
int fill_level_in_puffer = 0;
/** Füllstand für den out_puffer. */
int fill_level_out_puffer = 0;


/** Bytespeicher. */
unsigned char in_puffer[BUF_SIZE] = {0};

/** Bitspeicher. */
unsigned char out_puffer[BUF_SIZE] = {0};


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
    fill_level_out_puffer++;
}

extern bool has_next_bit(void)
{
    bool has_next_bit = false;

    if (position_bit > 7)
    {
        index_bit++;
        position_bit = 0;
    }

    if (index_bit < fill_level_in_puffer)
    {
        if (GET_BIT(in_puffer[index_bit], position_bit) == 0
                || GET_BIT(in_puffer[index_bit], position_bit) == 1)
        {
            has_next_bit = true;
        }
    }

    position_bit++;

    return has_next_bit;
}

extern BIT read_bit(void)
{
    return GET_BIT(in_puffer[index_bit], position_bit);
}

extern void write_bit(BIT c)
{
    out_puffer[index_bit] = PUT_BIT(out_puffer[index_bit], c, position_bit);
    fill_level_out_puffer = index_bit + 1;
}

extern void reset(void)
{
    index_byte = 0;
    
    index_bit = 0;
    position_bit = 0;

    fill_level_out_puffer = 0;
    fill_level_in_puffer = 0;
}
