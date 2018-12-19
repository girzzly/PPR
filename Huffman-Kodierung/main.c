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
#include "argument_validation.h"
#include "huffmann.h"
#include "io.h"

/**
 * Hier werden alle Funktionen aufgerufen.
 * @param argc Anzahl von übergebenen Argumenten.
 * @param argv Die einzelnen übergebenen Argumente.
 */
int main(int argc, char** argv)
{
    EXIT_CODES exit_code = process_arguments(argc, &argv);

    if (exit_code == SUCCESS_RUN)
    {
        char in[] = "abcdefghijklmnopqrstuvwxyz";
        char out[BUF_SIZE] = {0};
        copy_chars(in, out);
        //    copy_bits(in, out);
        PRINT_PUFFER(out, strlen((char*) out));

        {
            char in2[] = "0123456789";
            char out2[BUF_SIZE] = {0};
            copy_chars(in2, out2);
            //        copy_bits(in2, out2);
            PRINT_PUFFER(out2, strlen((char*) out2));
        }
    }
    else
    {
        printf("Program terminated with exit code %d.\n", exit_code);
    }

    return (exit_code);
}

