/** 
 * @file binary_heap.c
 * @author Dominik Krakau
 *
 * @date 2019-01-02
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "binary_heap.h"


/** Binärer Heap. */
static char *heap = "";

static char *preorder_heap = "";

/** Startadresse des Binären Heaps. */
static char **heap_reset = &heap;

/** Heapgröße. */
static int heap_size = 0;

/** Anzahl der Ebenen im Heap. */
static int heap_stage = 0;

/** Schrittgröße für die Erweiterung des Speichers für den Heap. */
static int heap_resize = 5;

/** Funktionszeiger um zwei Zeichen zu vergleichen. */
static HEAP_ELEM_COMP compare;

/** Funktionszeiger um ein Zeichen am Bildschirm auszugeben. */
static HEAP_ELEM_PRINT print_char;

static int get_root_of(int position);
static void get_preorder(char *min_heap);

extern void heap_init(HEAP_ELEM_COMP comp, HEAP_ELEM_PRINT print)
{
    compare = comp;
    print_char = print;

    heap = malloc(heap_resize);
}

extern void heap_destroy(void)
{
    free(heap);
    heap = NULL;
}

extern void heap_insert(void *element)
{
    if (heap_size == 0)
    {
        *heap = *((char *) element);
        heap_size++;
        heap_stage++;
    }
    else
    {
        if (heap_size % heap_resize == 0)
        {

            heap_resize = heap_resize + heap_resize;

            if (realloc(heap, heap_resize) == NULL)
            {
                printf("Can not resize heap!");
            }
        }

        strncat(heap, (char *) element, 1);
        heap_size++;

        // einsortieren!
        bool sorted = false;

        int last_index_element = strlen(heap) - 1;
        int root_index = get_root_of(last_index_element);

        //        printf("lastElement: %c , rootElement: %c\n", heap[last_index_element], heap[root_index]);

        while (!sorted)
        {
            // falsche compare methode!!!
            if (strcmp(&heap[last_index_element], &heap[root_index]) < 0) // dann tauschen!
            {
                char temp = heap[last_index_element];
                heap[last_index_element] = heap[root_index];
                heap[root_index] = temp;

                last_index_element = root_index;
                root_index = get_root_of(last_index_element);
            }
            else // dann weiter!
            {
                sorted = true;
            }
        }

        printf("%s\t%c\t%d\t%d\n", heap, *((char *) element), heap_resize, heap_size);

    }


}

extern bool heap_extract_min(void **min_element)
{
    bool extraction_successed = false;

    return extraction_successed;
}

extern void heap_print(void)
{
    if (heap_size == 0)
    {
        printf("Heap is empty!\n");
    }
    else
    {
        printf("Heap: (%d Elemente)\n", heap_size);
        printf("|-- %c\n", heap[0]);

        get_preorder(heap);
    }
}

static int get_root_of(int position)
{
    int subtrahend = 0;

    bool progress = false;

    int i;
    for (i = 0; i <= position; i++)
    {

        if (i == 0)
        {
            subtrahend = 0;
        }
        else if (i == 1)
        {
            subtrahend = -1;
        }
        else if (i > 1)
        {
            if (!progress)
            {
                subtrahend--;
                progress = true;
            }
            else
            {
                progress = false;
            }
        }
    }

    //     printf("%d%d = %d\n", position, subtrahend, position + subtrahend);

    return position + subtrahend;
}

static void get_preorder(char *min_heap)
{
    int min_heap_length = strlen(min_heap);

    char preorder_heap[min_heap_length];

    memset(&preorder_heap, '\0', min_heap_length);

    printf("preorderHeap: %s\n", (char *) preorder_heap);

    // convert min_heap to preorder_heap.
    double stage = 0.0;
    int i = 0;
    while (stage < min_heap_length)
    {        
        stage = pow(2.0, i);
        
        
        if (stage < min_heap_length)
        {
            stage = pow(2.0, i - 1);
            break;

        }
        
        i++;
    }

    printf("stage: %f\n", stage);


}

