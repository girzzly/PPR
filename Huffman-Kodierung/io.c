/** 
 * @file io.c
 * 
 * Das Modul io stellt die Funktionen zum byte- und bitweisen Lesen
 * und Schreiben zur Verf�gung.
 * 
 * @author Dominik
 *
 * @date 2018-11-06
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __unix__
#include <sys/stat.h>
#else
#include <sys\stat.h>
#endif
#include <time.h>

#include "huffmann_common.h"
#include "io.h"

/** 
 * Dieses Makro gibt ein Bit aus einem �bergebenen Byte
 * an einer bestimmten Position wieder. 
 */
#define GET_BIT(BYTE, POS) ( ( (BYTE) & ( 0x80 >> (POS) ) ) >> ( 7 - (POS) ) )

/** 
 * Dieses Makro setzt ein Bit an einer bestimmten
 * Position eines �bergebnenen Byte.
 */
#define PUT_BIT(BYTE, BIT, POS) ( (BIT) == ON ) \
                                   ? (BYTE) | ( 0x80 >> (POS) ) \
                                   : (BYTE) & ~( 0x80 >> (POS) )

/** 
 * Konstante f�r die Gr��e eines Bytes.
 */
#define BYTE_SIZE 8

/** Eingabestrom. */
static FILE *input_file_stream = NULL;

/** Ausgabestrom. */
static FILE *output_file_stream = NULL;

/** Index f�r den in_puffer. */
static int index_byte;

/** Index f�r den out_puffer. */
static int index_bit;
/** Position des Bits im Byte. */
static int position_bit;

/** F�llstand f�r den in_puffer. */
static int fill_level_in_puffer;
/** F�llstand f�r den out_puffer. */
static int fill_level_out_puffer;

/** Bytespeicher. */
static unsigned char in_puffer[BUF_SIZE];

/** Bitspeicher. */
static unsigned char out_puffer[BUF_SIZE];


/**
 * Setzt die Indexe und den F�llstand aller Puffer zur�ck.
 */
static void reset(void);

/**
 * Liest aus einer Datei die maximale Blockgr��e 
 * und schreibt den Inhalt in den in_puffer.
 * @return Gelesene Anzahl der Zeichen.
 */
static size_t read_next_block();

/**
 * Schreibt den Inhalt des out_puffers in eine Datei 
 * bis verbleibende Blockgr��e erreicht ist.
 * @return Geschriebene Anzahl der Zeichen.
 */
static size_t write_block();

/**
 * Verwaltet den Schreib- und Lesefluss f�r die Ein- und Ausgabedateien.
 */
static void manage_file(void);


extern bool has_next_char(void)
{
    manage_file();

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
    manage_file();

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

static void manage_file(void)
{ 
    if (fill_level_out_puffer == fill_level_in_puffer)
    {
        write_block();
        read_next_block();
    }
}

static void reset(void)
{
    index_byte = 0;

    index_bit = 0;
    position_bit = 0;

    fill_level_out_puffer = 0;
    fill_level_in_puffer = 0;
}

static size_t read_next_block()
{
    reset();
    size_t readed_blocks = fread(in_puffer, sizeof (char), BUF_SIZE, input_file_stream);
    fill_level_in_puffer = readed_blocks;

    return readed_blocks;
}

static size_t write_block()
{
    size_t writed_blocks = fwrite(out_puffer, sizeof (char), fill_level_out_puffer, output_file_stream);

    return writed_blocks;
}

extern EXIT_CODES open_infile(char *in_filename)
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    input_file_stream = fopen(in_filename, "rb");
    
//    reset();
    fill_level_in_puffer = 0;

    fread(in_puffer, sizeof (char), BUF_SIZE, input_file_stream);
    fill_level_in_puffer = strlen((char*) in_puffer);

    if (input_file_stream == NULL)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim oeffnen der Eingabedatei.");
        exit(exit_code);
    }
    
    return exit_code;
}

extern EXIT_CODES open_outfile(char *out_filename)
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    output_file_stream = fopen(out_filename, "wb");
    
    fill_level_out_puffer = 0;

    if (output_file_stream == NULL)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim oeffnen der Ausgabedatei.");
        exit(exit_code);
    }

    return exit_code;
}

extern EXIT_CODES close_infile()
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    if (fclose(input_file_stream) == EOF)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim schliessen der Eingabedatei.");
        exit(exit_code);
    }

    return exit_code;
}

extern EXIT_CODES close_outfile()
{
    EXIT_CODES exit_code = SUCCESS_RUN;

    write_block();

    if (fclose(output_file_stream) == EOF)
    {
        exit_code = IO_ERROR;
        printf("IO ERROR: Fehler beim schliessen der Ausgabedatei.");
        exit(exit_code);
    }

    return exit_code;
}

extern void show_info(char *in_filename, char *out_filename, clock_t prg_start, clock_t prg_end)
{
    printf("Ausfuehrungsstatistik\n");
    struct stat attribut;
    stat(in_filename, &attribut);
    printf(" - Groesse der Eingabedatei %s (byte): %ld\n", in_filename, attribut.st_size);
    stat(out_filename, &attribut);
    printf(" - Groesse der Ausgabedatei %s (byte): %ld\n", out_filename, attribut.st_size);
    printf(" - Die Laufzeit betrug %.2f Sekunden\n\n", (float) (prg_end - prg_start) / CLOCKS_PER_SEC);
}
