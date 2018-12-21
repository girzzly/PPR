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

extern void compress(char in_filename[], char out_filename[])
{
    open_infile((char *) in_filename);
    open_outfile((char *) out_filename);

    unsigned char c;

    while (has_next_char())
    {
        c = read_char();
        write_char(c);
    }

    close_infile();
    close_outfile();
}

extern void decompress(char in_filename[], char out_filename[])
{
    open_infile((char *) in_filename);
    open_outfile((char *) out_filename);

    BIT c;

    while (has_next_bit())
    {
        c = read_bit();
        write_bit(c);
    }

    close_infile();
    close_outfile();
}

