/** 
 * @file argument_validation.c
 * 
 * In diesem Modul werden die Argumente, die per Komandozeile übergeben werden
 * überprüft.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-12-19
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "huffmann_common.h"
#include "argument_validation.h"
#include "io.h"

char output_filename[MAX_FILENAME_LENGTH] = {'\0'};
char input_filename[MAX_FILENAME_LENGTH] = {'\0'};

bool compressed = false;
bool decompressed = false;
bool info = false;
bool help = false;

bool level = true;
int level_number = 2;

bool output_comand = false;

bool is_input_filename = false;

/**
 * Setzt die Variablenwerte zurück.
 */
static void reset_values();

EXIT_CODES process_arguments(int argc, char*** argv)
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    reset_values();

    int i;
    for (i = 1; i < argc; i++)
    {
        (*argv)++;

        if (strcmp(**argv, "-c") == 0)
        {
            if (decompressed == true)
            {
                decompressed = false;
            }

            compressed = true;
        }
        else if (strcmp(**argv, "-d") == 0)
        {
            if (compressed == true)
            {
                compressed = false;
            }

            decompressed = true;
        }
        else if (strcmp(**argv, "-v") == 0)
        {
            info = true;
        }
        else if (strcmp(**argv, "-h") == 0)
        {
            help = true;
        }
        else if (strcmp(**argv, "-o") == 0)
        {
            (*argv)++;
            i++;
            if (***argv != '-')
            {
                output_comand = true;
                strncpy(output_filename, **argv, strlen(**argv));
            }
            else
            {
                // -o option is set without outputname!
                exit_code = ARGUMENTS_ERROR;
            }
        }
        else
        {
            if (***argv == '-')
            {
                int comand_length = strlen(**argv);

                (*(*argv))++;
                if (***argv == 'l')
                {
                    (*(*argv))++;
                    if (***argv != '\0')
                    {
                        if (***argv > 48 && ***argv < 58 && comand_length == 3)
                        {
                            level_number = ***argv - 48;
                        }
                        else
                        {
                            // wrong level_number!
                            level = false;
                            level_number = 0;
                            exit_code = ARGUMENTS_ERROR;
                        }
                    }
                    else
                    {
                        // no level_number!
                        level = false;
                        level_number = 0;
                        exit_code = ARGUMENTS_ERROR;
                    }
                }
                else 
                {
                    // comand does not exsist or '-' sign but no comand!
                    exit_code = ARGUMENTS_ERROR;
                }
            }
            else if (***argv != '-' && i == argc - 1)
            {
                is_input_filename = true;
                strncpy(input_filename, **argv, strlen(**argv));
//                input_filename = **argv;
            }
            else
            {
                // filename already exsist or unknown comand!
                exit_code = ARGUMENTS_ERROR;
            }
        }
    }

    if (decompressed == true)
    {
        level = false;
        level_number = 0;
    }
    if (output_comand == false)
    {
        strncpy(output_filename, input_filename, strlen(input_filename));

        if (decompressed && is_input_filename)
        {
            strcat(output_filename, ".hd\0");

        }
        else
        {
            strcat(output_filename, ".hc\0");
        }
    }

    if ((exit_code == SUCCESS_RUN && (decompressed || compressed) && is_input_filename))
    {
        exit_code = SUCCESS_RUN;
    }
    else
    {
        exit_code = ARGUMENTS_ERROR;
    }

    printf("--------------------------------\n");
    printf("Compress: %d\n", compressed);
    printf("Decompress: %d\n", decompressed);
    printf("Level: %d   Level-Nr: %d\n", level, level_number);
    printf("Info: %d\n", info);
    printf("Help: %d\n", help);
    printf("Output: %d   %s\n", output_comand, (char *) output_filename);
    printf("Filename: %d   %s\n", is_input_filename, (char *) input_filename);
    printf("--------------------------------\n");

    return exit_code;
}

extern void showInfo()
{
    
}

extern void showHelp()
{
    
}

static void reset_values() 
{
    compressed = false;
    decompressed = false;
    info = false;
    help = false;

    level = true;
    level_number = 2;

    output_comand = false;
    is_input_filename = false;
}