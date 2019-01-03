/** 
 * @mainpage Erzeugung eines binären heaps.
 * 
 * @file main.c
 * @author Dominik
 * 
 * @date 2019-01-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "binary_heap.h"

/**
 * Diese Funktion vergleicht zwei Zeichen.
 * 
 * @param c1    Das erste Zeichen.
 * 
 * @param c2    Das zweite Zeichen.
 * 
 * @return      Liefert 0, wenn beide Zeichen gleich sind; 1, wenn c1 größer ist
 *              als c2; -1, wenn c1 kleiner ist als c2.
 */
int comp(char *c1, char *c2);

/**
 * Diese Funktion gibt das übergebene Zeichen als String am Bildschirm aus.
 * 
 * @param c     Das übergebene Zeichen.
 */
void print(char *c);

/**
 * Hier werden die Funktionen aufgerufen.
 */
int main(int argc, char** argv)
{
    bool passed;
    int i;
    char *letter = NULL;

    char *elements = "phnjabcgdi";
    char *expected = "abcdghijnp";
    char result[100];

    /* Heap initialisieren */
    heap_init((HEAP_ELEM_COMP) comp, (HEAP_ELEM_PRINT) print);

    /* Elemente in Heap einfügen */
    for (i = 0; i < (int) strlen(elements); i++)
    {
        heap_insert(&elements[i]);
    }
    
    /* Heap ausgeben */
    heap_print();
    
    /* Elemente der Größe nach aus dem Heap extrahieren */
//    i = 0;
//    while (heap_extract_min((void **) &letter))
//    {
//        result[i] = *letter;
//        i++;
//    }
//    result[i] = '\0';
//
//    /* Heap freigeben */
    heap_destroy();
//
//    /* Ergebnis und erwartetes Ergebnis vergleichen */
//    passed = strcmp(result, expected) == 0;
//    printf("Test %s\n", (passed) ? "passed" : "failed");
//    printf("%s\n", result);
//    printf("%s\n", expected);

    return (EXIT_SUCCESS);
}

int comp(char *c1, char *c2) {
    
    return (*c1 == *c2) 
            ? 0 
            : (*c1 > *c2) ? 1 : -1;
}

void print(char *c) {
    
    printf("%c", *c);
}

