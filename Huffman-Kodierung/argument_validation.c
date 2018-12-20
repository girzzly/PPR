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

/** Zeigt an, ob komprimiert werden soll. */
bool compressed = false;

/** Zeigt an, ob dekomprimiert werden soll. */
bool decompressed = false;

/** Zeigt an, ob Infos ausgegeben werden sollen. */
bool info = false;

/** Zeigt an, ob die Programmhilfe ausgegeben werden soll. */
bool help = false;

/** Zeigt an, ob ein Level für die Komprimierung gesetzt werden soll. */
bool level = true;

/** Levelnummer der Komprimierung. */
int level_number = 2;

/** Zeigt an, ob es ein -o Kommando gibt. */
bool output_comand = false;

/** Zeigt an, ob es sich um einen Input Filename handelt. */
bool is_input_filename = false;

/** Name der Inputdatei. */
static char input_filename[MAX_FILENAME_LENGTH] = {'\0'};

/** Name der Outputdatei. */
static char output_filename[MAX_FILENAME_LENGTH] = {'\0'};


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

    if (help || (exit_code == SUCCESS_RUN && (decompressed || compressed) && is_input_filename))
    {
        if (help)
        {
            showHelp();
        }
        
        exit_code = SUCCESS_RUN;
    }
    else
    {
        exit_code = ARGUMENTS_ERROR;
    }

    // Debugg Hilfe
//    printf("--------------------------------\n");
//    printf("Compress: %d\n", compressed);
//    printf("Decompress: %d\n", decompressed);
//    printf("Level: %d   Level-Nr: %d\n", level, level_number);
//    printf("Info: %d\n", info);
//    printf("Help: %d\n", help);
//    printf("Output: %d   %s\n", output_comand, (char *) output_filename);
//    printf("Filename: %d   %s\n", is_input_filename, (char *) input_filename);
//    printf("--------------------------------\n");

    return exit_code;
}

extern void showHelp()
{
    printf("Usage: huffmann_kodierung [OPTIONS]... [FILENAME]...\n");
    printf("Komprimiert oder Dekomprimiert Textdatein\nim Sinne der Huffman-Kodierung.\n\n");

    printf("Arguments:\n");
    printf("\t-c\tDie Eingabedatei wird komprimiert.\n\n");
    printf("\t-d\tDie Eingabedatei wird dekomprimiert.\n\n");
    
    printf("\t-h\tZeigt eine Hilfe an, die die Benutzung des Programms erklaert.\n\n");
    
    printf("\t-l\tLegt den Level der Komprimierung fest. Der Wert für den Level\n");
    printf("  \t\tfolgt ohne Leerzeichen auf die Option -l und muss zwischen 1\n");  
    printf("  \t\tund 9 liegen. Fehlt die Option, wird der Level standardmaessig\n");
    printf("  \t\tauf 2 eingestellt. Der Parameter wird ignoriert, wenn die Option\n");
    printf("  \t\t-d angegeben wurde.\n\n");
    
    printf("\t-o\tLegt den Namen der Ausgabedatei fest. Wird die Option weggelassen,\n");
    printf("  \t\twird der Name der Ausgabedatei standardmaessig festgelegt.\n");
    printf("  \t\tDazu wird bei einer Komprimierung der Dateiname um\n");
    printf("  \t\tie Endung .hc und bei einer Dekomprimierung um die\n");
    printf("  \t\tEndung .hd erweitert.\n\n");
    
    printf("\t-v\tGibt Informationen über die Komprimierung bzw. Dekomprimierung\n");
    printf("  \t\taus, mind. die Groesse der Ein- und der Ausgabedatei\n");
    printf("  \t\tsowie die Programmlaufzeit in Sekunden.\n\n");
    
    printf("\t<filename>\tName der Eingabedatei.\n\n");

    printf("Exsamples:\n");
    printf("\thuffman_codierung -h\n");
    printf("\thuffman_codierung -d <filename>\n");
    printf("\thuffman_codierung -c -v -l3 -o <outputfilename> <inputfilename>\n\n");
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

extern char* get_input_filename()
{
    char *p = input_filename;
    return p;
}

extern char* get_output_filename()
{
    char *p = output_filename;
    return p;
}