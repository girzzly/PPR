/** 
 * @file huffmann.c
 * 
 * Im Modul huffman wird die Komprimierung und Dekomprimierung realisiert.
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

extern void copy_chars(char in[], char out[])
{   
    unsigned char c;
    
    put_puffer_in(in);

    while (has_next_char())
    {
        c = read_char();
        write_char(c);
    }

    put_puffer_out(out);
}

extern void copy_bits(char in[], char out[])
{    
    BIT c;
    
    put_puffer_in(in);

    while (has_next_bit())
    {
        c = read_bit();
        write_bit(c);
    }

    put_puffer_out(out);
}

