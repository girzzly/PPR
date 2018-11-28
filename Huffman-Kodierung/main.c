/** 
 * @mainpage Huffmann-Codierung.
 * 
 * Mit diesem Programm soll es möglich sein,
 * die Huffmann-Codierung durchführen zu können.
 * 
 * @file main.c
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include <stdio.h>
#include <stdlib.h>

#include "huffmann_common.h"
#include "huffmann.h"
#include "io.h"

/**
 * Hier werden alle Funktionen aufgerufen.
 * @param argc Anzahl von übergebenen Argumenten.
 * @param argv Die einzelnen übergebenen Argumente.
 */
int main(int argc, char** argv)
{
    int i;

    char in[] = "abcdefghijklmnopqrstuvwxyz";
    char out[BUF_SIZE] = {0};

    copy_chars(in, out);
//        copy_bits(in, out);

    for (i = 0; i < fill_level_out_puffer; i++)
    {
        CPRINT(out[i]);
    }

    BR;

    {
        char in2[] = "0123456789";
        char out2[BUF_SIZE] = {0};

        copy_chars(in2, out2);
//                copy_bits(in2, out2);

        for (i = 0; i < fill_level_out_puffer; i++)
        {
            CPRINT(out2[i]);
        }
    }
    
//    XPRINTLN(fill_level_out_puffer);

    return 0;
}

