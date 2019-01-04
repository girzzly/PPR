/* ===========================================================================
 * Header-Dateien einbinden
 * ======================================================================== */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "frequency.h"


/* ===========================================================================
 * Makros
 * ======================================================================== */

/**
 * Makro zur Prüfung ob die Speicherallokation erfolgreich war: Ist die
 * übergebene Variable NULL, wird das Programm mit einer Fehlermeldung
 * abgebrochen.
 */
#define ASSERT_NOT_NULL(VAR) \
{if (VAR == NULL) { \
    fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno));\
    exit(EXIT_FAILURE); \
}}


/* ===========================================================================
 * Strukturdefinitionen
 * ======================================================================== */

/**
 * Setzt Wörter mit einer Häufigkeit in Beziehung
 */
struct FREQUENCY
{
    /**
     * Komponente für das Wort
     */
    char *word;
    /**
     * Komponente für die Anzahl der Wortvorkommen
     */
    int count;
};


/* ===========================================================================
 * Funktionsdefinitionen
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Funktion: create_frequency
 * ------------------------------------------------------------------------ */
extern struct FREQUENCY *create_frequency(const char *word, const int count)
{
    /* Speicher für die Struktur allokieren */
    struct FREQUENCY *p_frequency = malloc(sizeof (struct FREQUENCY));
    ASSERT_NOT_NULL(p_frequency);

    /* Komponenten der Struktur initialisieren */
    p_frequency->word = NULL;
    p_frequency->count = count;
    set_word_in_frequency(p_frequency, word);

    return p_frequency;
}

/* ---------------------------------------------------------------------------
 * Funktion: destroy_frequency
 * ------------------------------------------------------------------------ */
extern void destroy_frequency(struct FREQUENCY **pp_frequency)
{
    if (pp_frequency != NULL && *pp_frequency != NULL)
    {

#ifdef DEBUG
        /* Ausgabe der zu löschenden Daten zu Debugzwecken */
        printf("- Loesche struct Frequency ");
        print_frequency(*pp_frequency);
        printf(" \n");
#endif

        free((*pp_frequency)->word);  /* oder: free((**pp_frequency).word); */
        free(*pp_frequency);
        *pp_frequency = NULL;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: get_word_from_frequency
 * ------------------------------------------------------------------------ */
extern char *get_word_from_frequency(const struct FREQUENCY *p_frequency)
{
    char *copied_string = NULL;

    if (p_frequency != NULL && p_frequency->word != NULL)
    {
        /* Speicher für die Kopie allokieren */
        int word_length = (int) strlen(p_frequency->word);
        copied_string = malloc((word_length + 1) * sizeof (char));
        ASSERT_NOT_NULL(copied_string);

        strcpy(copied_string, p_frequency->word);
    }

    return copied_string;
}

/* ---------------------------------------------------------------------------
 * Funktion: get_count_from_frequency
 * ------------------------------------------------------------------------ */
extern int get_count_from_frequency(const struct FREQUENCY *p_frequency)
{
    int count = -1;

    if (p_frequency != NULL)
    {
        count = p_frequency->count;
    }

    return count;
}

/* ---------------------------------------------------------------------------
 * Funktion: set_word_in_frequency
 * ------------------------------------------------------------------------ */
extern void set_word_in_frequency(struct FREQUENCY *p_frequency, 
                                  const char *word)
{
    int word_length;

    if (p_frequency == NULL)
    {
        return;
    }

    /* Benötigten Speicherplatz abhängig vom übergebenen Wort ermitteln.
     * Wurde kein Wort angegeben, wird das alte Wort gelöscht. */
    if (word == NULL)
    {
        if (p_frequency->word != NULL)
        {
            free(p_frequency->word);
            p_frequency->word = NULL;
        }
    }
    else
    {
        word_length = (int) strlen(word);

        /* Speicher für das Wort allokieren */
        p_frequency->word =
                  (p_frequency->word == NULL)
                    ? malloc((word_length + 1) * sizeof (char))
                    : realloc(p_frequency->word,
                              (word_length + 1) * sizeof (char));
        ASSERT_NOT_NULL(p_frequency->word);

        /* Wort in die Struktur kopieren. */
        strcpy(p_frequency->word, word);
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: set_count_in_frequency
 * ------------------------------------------------------------------------ */
extern void set_count_in_frequency(struct FREQUENCY *p_frequency, 
                                   const int count)
{
    if (p_frequency != NULL)
    {
        p_frequency->count = count;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: cmp_frequency
 * ------------------------------------------------------------------------ */
extern int compare_frequency(const struct FREQUENCY *p_frequency1, 
        const struct FREQUENCY *p_frequency2)
{
    if (p_frequency1 != NULL && p_frequency2 != NULL
        && p_frequency1->word != NULL && p_frequency2->word != NULL) 
    {
        return (p_frequency1->count == p_frequency2->count 
                && (strcmp(p_frequency1->word, p_frequency2->word) == 0)) ? 0 : 1;
    }
    else 
    {
        return 1;
    }
}

/* ---------------------------------------------------------------------------
 * Funktion: get_frequency_as_string
 * ------------------------------------------------------------------------ */
extern char *get_frequency_as_string(const struct FREQUENCY *p_frequency)
{
    char *string;
    
    string = malloc(sizeof(char));
    strcpy(string, "");

    if (p_frequency != NULL)
    {
        /* Anzahl Stellen von count berechnen */
        int arity = 1;
        while (arity * 10 < p_frequency->count) 
        {
            arity++;
        }
        /* Inhalt der Struktur in String schreiben */
        if (p_frequency->word != NULL)
        {
            size_t length = strlen(p_frequency->word) * sizeof(char)
                            + arity + 5 * sizeof(char);
            string = malloc(length);
            ASSERT_NOT_NULL(string);
            snprintf(string, length, "[%s: %d]", 
                     p_frequency->word, p_frequency->count);
        }
        else 
        {
            snprintf(string, arity + 5 * sizeof(char), 
                     "[-: %d]", p_frequency->count);
        }
    }

    return string;
}

/* ---------------------------------------------------------------------------
 * Funktion: print_frequency
 * ------------------------------------------------------------------------ */
extern void print_frequency(const struct FREQUENCY *p_frequency)
{
    if (p_frequency != NULL  && p_frequency->word != NULL)
    {
        printf("[%s: %d]", p_frequency->word, p_frequency->count);
    }
}
