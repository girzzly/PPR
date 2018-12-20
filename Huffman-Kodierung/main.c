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

clock_t prg_start;
clock_t prg_end;

bool is_input_filename;
bool compresed;
bool decompresed;
bool info;
bool help;

/**
 * Hier werden alle Funktionen aufgerufen.
 * @param argc Anzahl von übergebenen Argumenten.
 * @param argv Die einzelnen übergebenen Argumente.
 */
int main(int argc, char** argv)
{
    prg_start = clock();
    
    EXIT_CODES exit_code = process_arguments(argc, &argv);

    if (exit_code == SUCCESS_RUN)
    {
        
        if(compresed && !help) {
            compress(input_filename, output_filename);
        }
        else if(!compresed && !help) {
            decompress(input_filename, output_filename);
        }
       
    }

    prg_end = clock();
    
    if(info && (compresed || decompresed) && is_input_filename)
    {
        showInfo(input_filename, output_filename, prg_start, prg_end);
    }
    
    printf("Program terminated with exit code %d.\n", exit_code);
    
    return (exit_code);
}

