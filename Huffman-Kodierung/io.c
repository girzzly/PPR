/** 
 * @mainpage Hauptseite.
 * 
 * @file io.c
 * @author Dominik
 *
 * @date Created on 6. November 2018, 12:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Maximale Puffergr��e. */
#define BUF_SIZE 4096

/** Index f�r den in_puffer. */
int index_byte = 0;

/** Index f�r den out_puffer. */
int index_bit = 0;
/** Position des Bits im Byte. */
int position_bit = 0;

/** F�llstand f�r den in_puffer. */
int fill_level_in_puffer = 0;
/** Bytespeicher. */
unsigned char in_puffer[BUF_SIZE] = {0};

/** F�llstand f�r den out_puffer. */
int fill_level_out_puffer = 0;
/** Bitspeicher. */
unsigned char out_puffer[BUF_SIZE] = {0};

/** Bitrepr�sentierung. */
typedef enum
{
    OFF,
    ON
} BIT;

/**
 * Diese Funktion gibt ein Bit aus einem �bergebenen Byte an einer bestimmten Position wieder.
 * @param c Das �bergebene Byte.
 * @param pos Die Position des Bits (0 h�chstwertige und 7 niederwertigste Bitselle).
 * @return Liefert das Bit an der anggebenen Posiion aus einem �bergebenen Byte.
 */
BIT get_bit(unsigned char c, int pos);

/**
 * Diese Funktion setzt ein Bit an einer bestimmten Position eines �bergebnenen Byte.
 * @param c Das �bergebenene Byte.
 * @param bit Das Bit was gesetzt werden soll.
 * @param pos Die Position an der das Bit im �bergebenen Byte gesetzt werden soll.
 * @return Liefert das ver�nderte Byte zur�ck.
 */
unsigned char put_bit(unsigned char c, BIT bit, int pos);

/**
 * Gibt an ob noch weitere Bytes aus dem Eingabepuffer gelesen werden k�nnen.
 * @return true falls n�chstes Byte vorhanden,
 *         false falls n�chstes Byte nicht vorhanden.
 */
bool has_next_char(void);

/**
 * Liefert mit jedem Aufruf das n�chste Byte aus dem Eingabepuffer.
 * (Wird nur aufgerufen, wenn noch ein weiteres Byte vorhanden ist.)
 * @return Das zu lesende Byte.
 */
unsigned char read_char(void);

/**
 * Schreibt ein Byte an die n�chste freie Position in den Ausgabepuffer.
 * @param c Das zu schreibende Byte.
 */
void write_char(unsigned char c);

/**
 * Gibt an, ob noch weitere Bits aus dem Eingabepuffer gelesen werden k�nnen.
 * @return true falls n�chstes Bit vorhanden,
 *         false falls n�chstes Bit nicht vorhanden.
 */
bool has_next_bit(void);

/**
 * Liefert mit jedem Aufruf das n�chste Bit aus dem Eingabepuffer.
 * (Wird nur aufgerufen, wenn noch ein weiteres Bit vorhanden ist.)
 * @return Das zu lesende Bit.
 */
BIT read_bit(void);

/**
 * Schreibt ein Bit an die n�chste freie Position in den Ausgabepuffer.
 * @param c Das zu schreibende Bit.
 */
void write_bit(BIT c);

/**
 * Kopiert den Eingabepuffer byteweise in den Ausgabepuffer.
 * @param in Das zu kopierende Array.
 * @param out Das fertig kopierte Array.
 */
void copy_chars(char in[], char out[]);

/**
 * Kopiert den EIngabepuffer bitweise in den Ausgabepuffer.
 * @param in Das zu kopierende Array.
 * @param out Das fertig kopierte Array.
 */
void copy_bits(char in[], char out[]);

/**
 * Setzt die Puffer und golaben Variabeln zur�ck.
 */
void reset(void);

/**
 * Hier werden alle Funktionen aufgerufen.
 * @param argc Anzahl von �bergebenen Argumenten.
 * @param argv Die einzelnen �bergebenen Argumente.
 */
int main(int argc, char** argv)
{
    int i;

    char in[] = "abcdefghijklmnopqrstuvwxyz";
    char out[BUF_SIZE] = {0};

//    copy_chars(in, out);
        copy_bits(in, out);

    for (i = 0; i < fill_level_in_puffer; i++)
    {
        printf("%c", out[i]);
    }

    printf("\n");

    {
        char in2[] = "0123456789";
        char out2[BUF_SIZE] = {0};

//        copy_chars(in2, out2);
                copy_bits(in2, out2);

        for (i = 0; i < fill_level_in_puffer; i++)
        {
            printf("%c", out2[i]);
        }
    }

    return 0;
}

BIT get_bit(unsigned char c, int pos)
{
    return (c & (0x80 >> pos)) >> (7 - pos);
}

unsigned char put_bit(unsigned char c, BIT bit, int pos)
{
    return (bit == ON)
            ? c | (0x80 >> pos)
            : c & ~(0x80 >> pos);
}

bool has_next_char(void)
{
    return index_byte < fill_level_in_puffer;
}

unsigned char read_char(void)
{
    return in_puffer[index_byte];
}

void write_char(unsigned char c)
{
    out_puffer[index_byte] = c;
    fill_level_out_puffer++;
}

bool has_next_bit(void)
{
    bool has_next_bit = false;

    if (position_bit > 7)
    {
        index_bit++;
        position_bit = 0;
    }

    if (index_bit < fill_level_in_puffer)
    {
        if (get_bit(in_puffer[index_bit], position_bit) == 0
                || get_bit(in_puffer[index_bit], position_bit) == 1)
        {
            has_next_bit = true;
        }
    }

    position_bit++;

    return has_next_bit;
    
//    return get_bit(in_puffer[index_bit], position_bit) == 0
//            || get_bit(in_puffer[index_bit], position_bit) == 1
//            ? true
//            : false;
}

BIT read_bit(void)
{
    return get_bit(in_puffer[index_bit], position_bit);
}

void write_bit(BIT c)
{
    out_puffer[index_bit] = put_bit(out_puffer[index_bit], c, position_bit);
    fill_level_out_puffer = index_bit + 1;
}

void copy_chars(char in[], char out[])
{
    unsigned char c;
    int length = strlen((char*) in);

    reset();

    strncpy((char*) in_puffer, (char*) in, length);

    fill_level_in_puffer = length;

    while (has_next_char())
    {
        c = read_char();
        write_char(c);

        index_byte++;
    }
    
    printf("\n%d\n", fill_level_out_puffer);

    strncpy((char*) out, (char*) out_puffer, length);
}

void copy_bits(char in[], char out[])
{
    BIT c;
    int length = strlen((char*) in);

    reset();

    strncpy((char*) in_puffer, (char*) in, length);

    fill_level_in_puffer = length;

    while (has_next_bit())
    {
        c = read_bit();
        write_bit(c);
    }
    
    printf("\n%d\n", fill_level_out_puffer);

    strncpy((char*) out, (char*) out_puffer, length);
}

void reset(void)
{
    index_byte = 0;
    
    index_bit = 0;
    position_bit = 0;

    fill_level_out_puffer = 0;
    fill_level_in_puffer = 0;
}
