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

/** Zeigt an, ob komprimiert werden soll. */
extern bool compressed;

/** Zeigt an, ob dekomprimiert werden soll. */
extern bool decompressed;

/** Zeigt an, ob Infos ausgegeben werden sollen. */
extern bool info;

/** Zeigt an, ob die Programmhilfe ausgegeben werden soll. */
extern bool help;

/** Zeigt an, ob ein Level f�r die Komprimierung gesetzt werden soll. */
extern bool level;

/** Levelnummer der Komprimierung. */
extern int level_number;

/** Zeigt an, ob es ein -o Kommando gibt. */
extern bool output_comand;

/** Zeigt an, ob es sich um einen Input Filename handelt. */
extern bool is_input_filename;

/**
 * Diese Funktion �berpr�ft die �bergebenen Komandozeielnargumente auf
 * Korrektheit.
 * @param argc Anzahl Komandozeilenargumente plus Programmname.
 * @param argv Die einzelenen Argumente in Stringform.
 * @return Liefert einen Exit Code zur�ck, SUCCESS_RUN wenn kein Fehler und
 *         ARGUMENT_ERROR falls die Komandozeilen Fehler aufweisen.
 */
extern EXIT_CODES process_arguments(int argc, char*** argv);

/**
 * Gibt Informationen �ber die Programmbenutzung am Bildschirm aus.
 */
extern void showHelp();

/**
 * Dise Funktion gibt den Inputfilenamen zur�ck.
 * @return Liefert einen Char-Pointer auf den Inputfilenamen zur�ck.
 */
extern char* get_input_filename();

/**
 * Dise Funktion gibt den Outputfilenamen zur�ck.
 * @return Liefert einen Char-Pointer auf den Outputfilenamen zur�ck.
 */
extern char* get_output_filename();

#endif

