/**
 * @file
 * Dieses Modul definiert eine Datenstruktur, mit der Worte mit einer
 * Häufigkeit in Beziehung gesetzt werden können, und stellt Funktionen
 * zu ihrer Verwaltung zur Verfügung.
 * 
 * @author  Ulrike Griefahn
 * @date    2015-12-04
 */

/* ------------------------------------------------------------------------- */
#ifndef _FREQUENCY_H
#define _FREQUENCY_H
/* ------------------------------------------------------------------------- */

/* ===========================================================================
 * Funktionsprototypen
 * ======================================================================== */

/**
 * Erzeut eine neue Struktur mit dem übergebenen Wort und der übergebenen 
 * Häufigkeit. Wird NULL übergeben, wird das Wort auf NULL gesetzt.
 *
 * @param word      das abzulegende Wort oder NULL                  
 * @param count     die abzulegende Häufigkeit
 * @return          die neu erzeugte Struktur
 */
extern struct FREQUENCY *create_frequency(const char *word, const int count);

/**
 * Löscht die Struktur und ihren Inhalt. Setzt den übergebenen Zeiger auf NULL.
 *
 * @param pp_frequency - die zu löschende Struktur
 */
extern void destroy_frequency(struct FREQUENCY **pp_frequency);

/**
 * Liefert eine neue Kopie des Worts der übergebenen Frequency-Struktur.
 * 
 * @param p_frequency   die übergebene Struktur
 * @return              Kopie des Worts der übergebenen Frequency-Struktur oder
 *                      NULL, wenn keine Struktur übergeben wurde oder die 
 *                      Struktur kein Wort enthält.
 */
extern char *get_word_from_frequency(const struct FREQUENCY *p_frequency);

/**
 * Liefert die Häufigkeit der übergebenen Frequency-Struktur.
 * 
 * @param p_frequency   die übergebene Struktur
 * @return              Häufigkeit der übergebenen Frequency-Struktur oder -1, 
 *                      wenn keine Struktur übergeben wurde.
 */
extern int get_count_from_frequency(const struct FREQUENCY *p_frequency);

/**
 * Ändert das Wort der übergebenen Struktur. Ist das übergebene Wort gleich
 * NULL, wird das Wort in der Struktur gelöscht.
 *
 * @param p_frequency   Zeiger auf die zu ändernde Struktur
 * @param word          das einzutragende Wort
 */
extern void set_word_in_frequency(struct FREQUENCY *p_frequency, 
                                  const char *word);

/**
 * Ändert die Häufigkeit in der übergebenen Struktur.
 * 
 * @param p_frequency   - Zeiger auf die zu ändernde Struktur
 * @param count         - die einzutragende Häufigkeit
 */
extern void set_count_in_frequency(struct FREQUENCY *p_frequency, 
                                   const int count);

/**
 * Vergleicht zwei Frequency-Strukturen miteinander. Die Funktion liefert 0, 
 * wenn beide Strukturen gleich sind, und 1 sonst. Wird keine Struktur oder 
 * eine Struktur ohne Wort übergeben, ist die Rückgabe immer 1.
 * 
 * @param p_frequency1 erste der zu vergleichenden Strukturen
 * @param p_frequency2 zweite der zu vergleichenden Strukturen
 * @return 0, wenn beide Strukturen gleich sind, und 1, sonst
 */
extern int compare_frequency(const struct FREQUENCY *p_frequency1, 
                             const struct FREQUENCY *p_frequency2);

/**
 * Gibt eine Textdarstellung der übergebenen Struktur als String aus.
 * 
 * @param p_frequency   die auszugebende Struktur
 * @return              Textdarstellung der Struktur
 */
extern char *get_frequency_as_string(const struct FREQUENCY *p_frequency);

/**
 * Gibt die Daten der übergebenen Struktur auf dem Bildschirm aus.
 * 
 * @param p_frequency   die auszugebende Struktur
 */
extern void print_frequency(const struct FREQUENCY *p_frequency);

/* ------------------------------------------------------------------------ */
#endif
