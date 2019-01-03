/** 
 * @file binary_heap.h
 * @author Dominik Krakau
 *
 * @date 2019-01-02
 */

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdbool.h>

/** Funktions-Typdefinition für Funktion comp. */
typedef void (*HEAP_ELEM_PRINT) (void*);

/** 
 * Funktions-Typdefinition für Funktion print.
 * 
 */
typedef int (*HEAP_ELEM_COMP) (void*, void*);

/**
 * Diese Funktion initialisiert den Heap. 
 * 
 * @param comp          Funktion, mit der Heap-Elemente verglichen werden
 *                      können.
 * 
 * @param print         Funktion, mit der Heap-Elemente auf dem Bildschrim
 *                      ausgegeben werden können.
 */
extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print);

/**
 * Diese Funktion löscht den Heap. (Gibt den Speicher wieder frei).
 */
extern void heap_destroy(void);

/**
 * Diese Funktion fügt ein neues Element in den Heap ein und sorgt dafür,
 * dass die Heap-Eigentschaft aufrechterhalten bleibt.
 * 
 * @param element       Das einzufügende Element.
 */
extern void heap_insert(void *element);

/**
 * Diese Funktion entfernt das kleinste Element aus dem Heap (dies ist immer
 * die Wurzel des Heaps). Diese Funktion sorgt ebenfalls dafür,
 * dass die Heap-Eigentschaft aufrechterhalten bleibt.
 * 
 * @param min_element   Zeiger für das kleinste Element im Heap.
 * 
 * @return              Liefet true, wenn ein Element erfolgreich extrahiert
 *                      werden konnte, und false, wenn der Heap beim Aufruf
 *                      bereits leer ist.
 */
extern bool heap_extract_min(void **min_element);

/**
 * Diese Funktion gibt den Heap auf dem Bildschirm aus.
 * Die Heap-Eigentschaft muss immer erfüllt sein.
 */
extern void heap_print(void);


#endif
