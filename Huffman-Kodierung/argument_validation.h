/** 
 * @file argument_validation.h
 * 
 * In diesem Modul werden die Argumente, die per Komandozeile übergeben werden
 * überprüft.
 * 
 * @author Dominik Krakau
 *
 * @date 2018-12-19
 */

#ifndef ARGUMENT_VALIDATION_H
#define ARGUMENT_VALIDATION_H

/** Maximale Dateinamenlänge. */
#define MAX_FILENAME_LENGTH 256

/**
 * Diese Funktion überprüft die übergebenen Komandozeielnargumente auf
 * Korrektheit.
 * @param argc Anzahl Komandozeilenargumente plus Programmname.
 * @param argv Die einzelenen Argumente in Stringform.
 * @return Liefert einen Exit Code zurück, SUCCESS_RUN wenn kein Fehler und
 *         ARGUMENT_ERROR falls die Komandozeilen Fehler aufweisen.
 */
extern EXIT_CODES process_arguments(int argc, char*** argv);

#endif

