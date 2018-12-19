/** 
 * @file io.c
 * 
 * Das Modul io stellt die Funktionen zum byte- und bitweisen Lesen
 * und Schreiben zur Verfügung.
 * 
 * @author Dominik
 *
 * @date 2018-11-06
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "huffmann_common.h"
#include "io.h"

/** 
 * Dieses Makro gibt ein Bit aus einem übergebenen Byte
 * an einer bestimmten Position wieder. 
 */
#define GET_BIT(BYTE, POS) ( ( (BYTE) & ( 0x80 >> (POS) ) ) >> ( 7 - (POS) ) )

/** 
 * Dieses Makro setzt ein Bit an einer bestimmten
 * Position eines übergebnenen Byte.
 */
#define PUT_BIT(BYTE, BIT, POS) ( (BIT) == ON ) \
                                   ? (BYTE) | ( 0x80 >> (POS) ) \
                                   : (BYTE) & ~( 0x80 >> (POS) )

/** 
 * Konstante für die Größe eines Bytes.
 */
#define BYTE_SIZE 8

/** Eingabestrom. */
static FILE *input_file_stream = NULL;

/** Ausgabestrom. */
static FILE *output_file_stream = NULL;

/** Index für den in_puffer. */
static int index_byte;

/** Index für den out_puffer. */
static int index_bit;
/** Position des Bits im Byte. */
static int position_bit;

/** Füllstand für den in_puffer. */
static int fill_level_in_puffer;
/** Füllstand für den out_puffer. */
static int fill_level_out_puffer;


/** Bytespeicher. */
static unsigned char in_puffer[BUF_SIZE];

/** Bitspeicher. */
static unsigned char out_puffer[BUF_SIZE];

extern bool has_next_char(void)
{
    return index_byte < fill_level_in_puffer;
}

extern unsigned char read_char(void)
{
    return in_puffer[index_byte];
}

extern void write_char(unsigned char c)
{
    out_puffer[index_byte] = c;
    index_byte++;
    fill_level_out_puffer++;
}

extern bool has_next_bit(void)
{
    return (index_bit < fill_level_in_puffer) && (position_bit < BYTE_SIZE);
}

extern BIT read_bit(void)
{
    return GET_BIT(in_puffer[index_bit], position_bit);
}

extern void write_bit(BIT c)
{
    out_puffer[index_bit] = PUT_BIT(out_puffer[index_bit], c, position_bit);

    position_bit++;

    if (position_bit >= BYTE_SIZE)
    {
        position_bit = 0;
        index_bit++;
    }

    fill_level_out_puffer = index_bit;
}

extern void reset(void)
{
    index_byte = 0;

    index_bit = 0;
    position_bit = 0;

    fill_level_out_puffer = 0;
    fill_level_in_puffer = strlen((char*) in_puffer);
}

extern EXIT_CODES open_infile(char *in_filename)
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    input_file_stream = fopen(in_filename, "rb");

    if (input_file_stream == NULL)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim öffnen der Eingabedatei.");
        exit(exit_code);
    }
    else
    {
        memset(out_puffer, '\0', BUF_SIZE);
        printf("Eingabedatei \'%s\' wurde geoeffnet.\n", in_filename);
        
        // read file
        fread(in_puffer, sizeof(char), BUF_SIZE, input_file_stream);
        printf("Eingabe-Text: %s\n", in_puffer);
    }

    return exit_code;
}

extern EXIT_CODES open_outfile(char *out_filename)
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    output_file_stream = fopen(out_filename, "wb");

    if (output_file_stream == NULL)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim öffnen der Ausgabedatei.");
        exit(exit_code);
    }
    else
    {
        memset(in_puffer, '\0', BUF_SIZE);
        printf("Ausgabedatei \'%s\' wurde geoeffnet.\n", out_filename);
    }
    
    return exit_code;
}

extern EXIT_CODES close_infile()
{
    EXIT_CODES exit_code = SUCCESS_RUN;
    
    if(fclose(input_file_stream) == EOF)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim schliessen der Eingabedatei.");
        exit(exit_code);
    }
    else
    {
        printf("Eingabedatei \'%s\' wurde geschlossen.\n", input_filename);
    }

    return exit_code;
}

extern EXIT_CODES close_outfile()
{
    EXIT_CODES exit_code = SUCCESS_RUN;
fwrite(out_puffer, sizeof(char), BUF_SIZE, output_file_stream);
    if(fclose(output_file_stream) == EOF)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim schliessen der Ausgabedatei.");
        exit(exit_code);
    }
    else
    {
        printf("Ausagbedatei \'%s\' wurde geschlossen.\n", output_filename);
        
        // Inhalt des Ausgabepuffers vorher noch einmal in die Ausgabedatei geschrieben.
        // out_puffer in Ausgabedatei schreiben! - fwirte
        fwrite(out_puffer, sizeof(char), BUF_SIZE, output_file_stream);
        printf("Ausgabedatei-Text: %s\t%d\n", out_puffer, output_file_stream);
    }
    
    return exit_code;
}