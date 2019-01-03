/** 
 * @file binary_heap.c
 * @author Dominik Krakau
 *
 * @date 2019-01-02
 */

#include <stdlib.h>
#include <stdio.h>
#include "binary_heap.h"

/** Der tatsächliche Füllstand des Heaps. */
#define FILL_LEVEL heap_size - heap_free_space


/** Schrittgröße für die Erweiterung des Speichers für den Heap. */
static int heap_resize = 5;

/** Heapgröße. */
static int heap_size = 0;

/** Freie Speicherelemente im Heap. */
static int heap_free_space = 0;

/** Heap durch ein Array aus void Zeigern (void *heap[]). */
static void **heap;

/** Funktionszeiger um zwei Zeichen zu vergleichen. */
static HEAP_ELEM_COMP comp_elements;

/** Funktionszeiger um ein Zeichen am Bildschirm auszugeben. */
static HEAP_ELEM_PRINT print_element;

/**
 * Diese Funktion Minimiert den Heap.
 * 
 * @param i
 */
static void min_heapify(int i);

/**
 * Diese Funktion gibt das linke Kind eines Knotens aus.
 *
 * @param x      Knoten von dem das linke Kind ausgegeben werden soll.
 * 
 * @return       Liefert den linken Kindknoten zurück.
 */
static int left_child(int x);

/**
 * Diese Funktion gibt das rechte Kind eines Knotens aus.
 *
 * @param x      Knoten von dem das rechte Kind ausgegeben werden soll.
 * 
 * @return       Liefert den rechte Kindknoten zurück.
 */
static int right_child(int x);

/**
 * Diese Funktion gibt den Elternknoten eines Knotens aus.
 * 
 * @param x     Knoten vom dem die Wurzel berechnet werden soll.
 * 
 * @return      Liefert den Wurzelknoten eines Kindknotens zurück. 
 */
static int parent(int x);


extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print)
{
    comp_elements = comp;
    print_element = print;

    heap = malloc(heap_resize * sizeof (void*));

    heap_size = heap_resize;
    heap_free_space = heap_resize;
}

extern void heap_destroy(void)
{
    free(heap);
    heap = NULL;
}

extern void heap_insert(void *element)
{
    int i;

    if (heap_free_space == 0)
    {
        void** p_temp;
        p_temp = realloc(heap, (heap_size + heap_resize) * sizeof *heap);

        if (p_temp != NULL)
        {
            heap_free_space = heap_resize;
            heap_size = heap_size + heap_free_space;
            heap = p_temp;
        }
        else
        {
            printf("Can not resize Heap.\n");
            exit(EXIT_FAILURE);
        }
    }

    heap_free_space--;
    
    i = FILL_LEVEL - 1;
    
    heap[i] = element;

    while (i != 0 && comp_elements(heap[parent(i)], heap[i]) == 1)
    {
        void *temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
    }
}

extern bool heap_extract_min(void **min_element)
{
    
    if (FILL_LEVEL <= 0)
    {
        return false;
    }
    else if (FILL_LEVEL == 1)
    {
        heap_free_space++;
        *min_element = heap[0];
        
        return true;
    }

    if (heap_free_space == heap_resize)
    {
        void **temp_p;
        temp_p = realloc(heap, (FILL_LEVEL) * sizeof *heap);
        
        if (temp_p != NULL)
        {
            heap_free_space = 0;
            heap_size -= heap_resize;
            heap = temp_p;
        }
        else
        {
            printf("Can not resize Heap.\n");
            exit(EXIT_FAILURE);
        }
    }

    *min_element = heap[0];
    heap[0] = heap[FILL_LEVEL - 1];
    
    heap_free_space++;
    
    min_heapify(0);

    return true;
}

extern void heap_print(void)
{

    // TO do.

}

static void min_heapify(int i)
{
    int smallest = i;
    
    int left = left_child(i);
    int right = right_child(i);

    if (left < FILL_LEVEL && comp_elements(heap[left], heap[i]) == -1)
    {
        smallest = left;
    }

    if (right < FILL_LEVEL && comp_elements(heap[right], heap[smallest]) == -1)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        void *temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        
        min_heapify(smallest);
    }
}

static int left_child(int x)
{
    return 2 * x + 1;
}

static int right_child(int x)
{
    return 2 * x + 2;
}

static int parent(int x)
{
    return (x - 1) / 2;
}

