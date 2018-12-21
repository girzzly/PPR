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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "huffmann_common.h"
#include "argument_validation.h"
#include "io.h"

extern EXIT_CODES process_arguments(int argc, char*** argv,
                             bool *compressed, bool *decompressed,
                             bool *info, bool *help,
                             bool *level, int *level_number,
                             bool *output_comand, bool *is_input_filename,
                             char **output_filename, char **input_filename)
{

    EXIT_CODES exit_code = SUCCESS_RUN;

    *compressed = false;
    *decompressed = false;

    *info = false;
    *help = false;

    *level = true;
    *level_number = 2;

    *output_comand = false;

    *is_input_filename = false;

    int i;
    for (i = 1; i < argc; i++)
    {
        (*argv)++;

        if (strcmp(**argv, "-c") == 0)
        {
            if (*decompressed == true)
            {
                *decompressed = false;
            }

            *compressed = true;
        }
        else if (strcmp(**argv, "-d") == 0)
        {
            if (*compressed == true)
            {
                *compressed = false;
            }

            *decompressed = true;
        }
        else if (strcmp(**argv, "-v") == 0)
        {
            *info = true;
        }
        else if (strcmp(**argv, "-h") == 0)
        {
            *help = true;
        }
        else if (strcmp(**argv, "-o") == 0)
        {
            (*argv)++;
            i++;
            if (***argv != '-')
            {
                *output_comand = true;
                *output_filename = **argv;
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
                            *level_number = ***argv - 48;
                        }
                        else
                        {
                            // wrong level_number!
                            *level = false;
                            *level_number = 0;
                            exit_code = ARGUMENTS_ERROR;
                        }
                    }
                    else
                    {
                        // no level_number!
                        *level = false;
                        *level_number = 0;
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
                *is_input_filename = true;
                *input_filename = **argv;
            }
            else
            {
                // filename already exsist or unknown comand!
                exit_code = ARGUMENTS_ERROR;
            }
        }
    }

    if (*decompressed == true)
    {
        *level = false;
        *level_number = 0;
    }
    
    if (*output_comand == false)
    {       
        *output_filename = malloc((strlen(*input_filename) + 4) * sizeof (char));
        strncpy(*output_filename, *input_filename, strlen(*input_filename));

        if (*decompressed && *is_input_filename)
        {
            strncat(*output_filename, ".hd", strlen(*output_filename));

        }
        else
        {
            strncat(*output_filename, ".hc", strlen(*output_filename));
        } 
    } 
    else {
        if (strcmp(*input_filename, *output_filename) == 0) // output and input have same names!
        {
            exit_code = ARGUMENTS_ERROR;
        }
    }
    
    if(fopen(*input_filename, "rb") == NULL) // file does not exists!
    {
        exit_code = ARGUMENTS_ERROR;
    }

    if (*help || (exit_code == SUCCESS_RUN && (*decompressed || *compressed) && *is_input_filename))
    {
        exit_code = SUCCESS_RUN;
    }
    else
    {
        exit_code = ARGUMENTS_ERROR;
    }

    if (*help)
    {
        show_help();
    }

    // Debugg Hilfe
    printf("--------------------------------\n");
    printf("Compress: %d\n", *compressed);
    printf("Decompress: %d\n", *decompressed);
    printf("Level: %d   Level-Nr: %d\n", *level, *level_number);
    printf("Info: %d\n", *info);
    printf("Help: %d\n", *help);
    printf("Output: %d   %s\n", *output_comand, *output_filename);
    printf("Filename: %d   %s\n", *is_input_filename, *input_filename);
    printf("--------------------------------\n");

    return exit_code;
}

extern void show_help()
{
    printf("Benutzung: huffmann_kodierung [OPTIONS]... [FILENAME]...\n"
           "Komprimiert oder Dekomprimiert Textdatein\nim Sinne der Huffman-Kodierung.\n\n"

           "Argumente:\n"
           "\t-c\tDie Eingabedatei wird komprimiert.\n\n"
           "\t-d\tDie Eingabedatei wird dekomprimiert.\n\n"

           "\t-h\tZeigt eine Hilfe an, die die Benutzung des Programms erklaert.\n\n"

           "\t-l\tLegt den Level der Komprimierung fest. Der Wert für den Level\n"
           "  \t\tfolgt ohne Leerzeichen auf die Option -l und muss zwischen 1\n"
           "  \t\tund 9 liegen. Fehlt die Option, wird der Level standardmaessig\n"
           "  \t\tauf 2 eingestellt. Der Parameter wird ignoriert, wenn die Option\n"
           "  \t\t-d angegeben wurde.\n\n"

           "\t-o\tLegt den Namen der Ausgabedatei fest. Wird die Option weggelassen,\n"
           "  \t\twird der Name der Ausgabedatei standardmaessig festgelegt.\n"
           "  \t\tDazu wird bei einer Komprimierung der Dateiname um\n"
           "  \t\tie Endung .hc und bei einer Dekomprimierung um die\n"
           "  \t\tEndung .hd erweitert.\n\n"

           "\t-v\tGibt Informationen über die Komprimierung bzw. Dekomprimierung\n"
           "  \t\taus, mind. die Groesse der Ein- und der Ausgabedatei\n"
           "  \t\tsowie die Programmlaufzeit in Sekunden.\n\n"

           "\t<filename>\tName der Eingabedatei.\n\n"

           "Beispiele:\n"
           "\thuffman_codierung -h\n"
           "\thuffman_codierung -d <filename>\n"
           "\thuffman_codierung -c -v -l3 -o <outputfilename> <inputfilename>\n\n");
}