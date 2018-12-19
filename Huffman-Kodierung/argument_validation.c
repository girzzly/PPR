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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "huffmann_common.h"
#include "argument_validation.h"

/** Name der Input-Datei. */
char *input_filename = NULL;

/** Name der Output-Datei. */
char output_filename[MAX_FILENAME_LENGTH] = {'\0'};


EXIT_CODES process_arguments(int argc, char*** argv)
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    bool compress = false;
    bool decompress = false;
    bool info = false;
    bool help = false;

    bool level = true;
    int level_number = 2;

    bool output_comand = false;

    bool is_input_filename = false;

    int i;
    for (i = 1; i < argc; i++)
    {
        (*argv)++;

        if (strcmp(**argv, "-c") == 0)
        {
            if (decompress == true)
            {
                decompress = false;
            }

            compress = true;
        }
        else if (strcmp(**argv, "-d") == 0)
        {
            if (compress == true)
            {
                compress = false;
            }

            decompress = true;
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
                            exit_code = ARGUMENTS_ERROR;
                        }
                    }
                    else
                    {
                        // no level_number!
                        exit_code = ARGUMENTS_ERROR;
                    }
                }
            }
            else if (***argv != '-' && i == argc - 1)
            {
                is_input_filename = true;
                input_filename = **argv;
            }
            else
            {
                // filename already exsist or unknown comand!
                exit_code = ARGUMENTS_ERROR;
            }
        }
    }

    if (decompress == true)
    {
        level = false;
        level_number = 0;
    }
    if (output_comand == false)
    {
        strncpy(output_filename, input_filename, strlen(input_filename));

        if (decompress && is_input_filename)
        {
            strcat(output_filename, ".hd\0");
            
        }
        else
        {
            strcat(output_filename, ".hc\0");
        }
    }

    if ((exit_code == SUCCESS_RUN && (decompress || compress) && is_input_filename))
    {
        exit_code = SUCCESS_RUN;
    }
    else
    {
        exit_code = ARGUMENTS_ERROR;
    }

    printf("--------------------------------\n");
    printf("Compress: %d\n", compress);
    printf("Decompress: %d\n", decompress);
    printf("Level: %d   Level-Nr: %d\n", level, level_number);
    printf("Info: %d\n", info);
    printf("Help: %d\n", help);
    printf("Output: %d   %s\n", output_comand, (char *)output_filename);
    printf("Filename: %d   %s\n", is_input_filename, input_filename);
    printf("--------------------------------\n");

    return exit_code;
}