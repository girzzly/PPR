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
#include <string.h>
#include <stdbool.h>

#include "huffmann_common.h"
#include "huffmann.h"
#include "io.h"

#define MAX_FILENAME_LENGTH 256

EXIT_CODES process_arguments(int argc, char*** argv);
void check_comands(char **comand);

char *input_filename = NULL;
char output_filename[MAX_FILENAME_LENGTH] = {'\0'};

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

    printf("--------------------------------\n");

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

void check_comands(char **comand)
{
    printf("%s\n", *comand);
}

