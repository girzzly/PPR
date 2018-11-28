/** 
 * @file huffmann.c
 * 
 * In diesem Modul... 
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include <stdio.h>
#include <string.h>

#include "huffmann_common.h"
#include "huffmann.h"
#include "io.h"

extern unsigned char in_puffer[BUF_SIZE];
extern unsigned char out_puffer[BUF_SIZE];

extern void copy_chars(char in[], char out[])
{
    unsigned char c;
    int length = strlen((char*) in);

    reset();

    strncpy((char*) in_puffer, (char*) in, length);

    fill_level_in_puffer = length;

    while (has_next_char())
    {
        c = read_char();
        write_char(c);

        index_byte++;
    }
    
//    DPRINTLN(fill_level_in_puffer);

    strncpy((char*) out, (char*) out_puffer, length);
}

extern void copy_bits(char in[], char out[])
{
    BIT c;
    int length = strlen((char*) in);

    reset();

    strncpy((char*) in_puffer, (char*) in, length);

    fill_level_in_puffer = length;

    while (has_next_bit())
    {
        c = read_bit();
        write_bit(c);
    }
    
//    DPRINTLN(fill_level_in_puffer);

    strncpy((char*) out, (char*) out_puffer, length);
}

