/** 
 * @mainpage Huffmann-Codierung.
 * 
 * Mit diesem Programm soll es m�glich sein,
 * die Huffmann-Codierung durchf�hren zu k�nnen.
 * 
 * @file main.c
 * 
 * @author Dominik Krakau
 *
 * @date 2018-11-27
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "huffmann_common.h"
#include "argument_validation.h"
#include "huffmann.h"
#include "io.h"

/**
 * Hier werden alle Funktionen aufgerufen.
 * @param argc Anzahl von �bergebenen Argumenten.
 * @param argv Die einzelnen �bergebenen Argumente.
 */
int main(int argc, char** argv)
{
    /* Programmstartzeit. */
    clock_t prg_start;

    /* Programmendzeit. */
    clock_t prg_end;

    /* Zeigt an, ob komprimiert werden soll. */
    bool compressed;

    /* Zeigt an, ob dekomprimiert werden soll. */
    bool decompressed;

    /* Zeigt an, ob Infos ausgegeben werden sollen. */
    bool info;

    /* Zeigt an, ob die Programmhilfe ausgegeben werden soll. */
    bool help;

    /* Zeigt an, ob ein Level f�r die Komprimierung gesetzt werden soll. */
    bool level;

    /* Levelnummer der Komprimierung. */
    int level_number;

    /* Zeigt an, ob es ein -o Kommando gibt. */
    bool output_comand;

    /* Zeigt an, ob es sich um einen Input Filename handelt. */
    bool is_input_filename;

    /* Name der Inputdatei. */
    char *input_filename = "";

    /* Name der Outputdatei. */
    char *output_filename = "";
    
    prg_start = clock();

    EXIT_CODES exit_code = process_arguments(argc, &argv,
                                             &compressed,
                                             &decompressed,
                                             &info, &help,
                                             &level, &level_number,
                                             &output_comand,
                                             &is_input_filename,
                                             &output_filename,
                                             &input_filename);
    
    
    
    char in_filename[MAX_FILENAME_LENGTH] = {'\0'};
    char out_filename[MAX_FILENAME_LENGTH] = {'\0'};
    strncpy(in_filename, input_filename, strlen(input_filename));
    strncpy(out_filename, output_filename, strlen(output_filename));

    if (exit_code == SUCCESS_RUN)
    {

        if (compressed && !help)
        {
            compress(input_filename, output_filename);
        }
        else if (!compressed && !help)
        {
            decompress(input_filename, output_filename);
        }

    }

    prg_end = clock();

    if (info && (compressed || decompressed) && is_input_filename)
    {
        showInfo(in_filename, out_filename, prg_start, prg_end);
    }

    printf("Program terminated with exit code %d.\n", exit_code);

    return (exit_code);
}

