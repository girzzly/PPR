/** 
 * @file argument_validation.h
 * 
 * In diesem Modul werden die Argumente, die per Komandozeile �bergeben werden
 * �berpr�ft.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-12-19
 */

#include <stdbool.h>

#include "huffmann_common.h"

#ifndef _ARGUMENT_VALIDATION_H
#define _ARGUMENT_VALIDATION_H

/**
 * Diese Funktion �berpr�ft die �bergebenen Komandozeielnargumente auf
 * Korrektheit.
 * @param argc              Anzahl Komandozeilenargumente plus Programmname.
 * @param argv              Die einzelenen Argumente in Stringform.
 * @param compressed        Zeiger zur Pr�fung auf Komprimierung.
 * @param decompressed      Zeiger zur Pr�fung auf Dekomprimierung.
 * @param info              Zeiger zur Pr�fung auf Informaitonsanzeige.
 * @param help              Zeiger zur Pr�fung auf Hilfsanzeige.
 * @param level             Zeiger zur Pr�fung auf gesetztes Level.
 * @param level_number      Gibt das Komprimierungslevel an.
 * @param output_comand     Gibt an ob eine Outputoption angegeben wurde.
 * @param is_input_filename Gibt an ob ein Inputfile angegegben wurde.
 * @param output_filename   Name des Outputfiles.
 * @param input_filename    Name des Inputfiles.
 * @return Liefer einen Error Code zur�ck. SUCCESS_RUN wenn kein Fehler vorliegt,
 *         ansonsten ARGUMENTS_ERROR.
 */
extern EXIT_CODES process_arguments(int argc, char*** argv,
                             bool *compressed, bool *decompressed,
                             bool *info, bool *help,
                             bool *level, int *level_number,
                             bool *output_comand, bool *is_input_filename,
                             char **output_filename, char **input_filename);

/**
 * Gibt Informationen �ber die Programmbenutzung am Bildschirm aus.
 */
extern void showHelp();

#endif

