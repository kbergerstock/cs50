/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 *
 * Keith R. Bergerstock
 */

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef unsigned char byte;

typedef struct Jpegs
{
    char  name[25];
    int   num_read;
    int   picture;
    int   found;
    byte *block;
} JPEG;

enum
{
    SUCCESS = 0,
    ERR_NO_ARG,
    ERR_OPEN_CARD_FILE,
    ERR_READ_CARD_FILE,
    ERR_OPEN_JPG_FILE,
    ERR_WRITE_JPG_FILE,
    ERR_NO_MEM,
    ERR_EXCEPTION,
    FEOF = 100,
    NOP,
} MSGS;

// read into buffer BLOCKSIZE data
// retirns    read successful
//            EOF found
//            general read error
int readBlock(FILE *fp, JPEG *jpg)
{
    int rtv;

    jpg-> num_read = fread(jpg->block, sizeof(byte), BLOCK_SIZE, fp);

    rtv = (jpg->num_read == BLOCK_SIZE) ? SUCCESS : FEOF;

    return rtv;
}

// write to file BLOCKSIZE data
// returns   unable to open file error
//           general write error
//           success
// opening and closing the file around the write keeps the file safe
int writeBlock(JPEG *jpg)
{
    int rtv = NOP;

    FILE *fp = fopen(jpg->name, "a");

    if (fp == NULL)
    {
        rtv = ERR_OPEN_JPG_FILE;
    }
    else
    {
        // append data to end of the file
        rtv = (fwrite(jpg->block, sizeof(byte), jpg->num_read, fp) == jpg->num_read) ? SUCCESS : ERR_WRITE_JPG_FILE;
    }
    fclose(fp);

    return rtv;
}

int process_block(JPEG *jpg)
{
    int rtv = NOP;

    byte b0 = jpg->block[0];
    byte b1 = jpg->block[1];
    byte b2 = jpg->block[2];
    byte b3 = jpg->block[3];

    b3 &= (byte)0xe0;
    // if the bytes defining the start of a jpeg are present
    // then start a new file
    if (b0 == (byte)0xff && b1 == (byte)0xd8 && b2 == (byte)0xff && b3 == (byte)0xe0)
    {
        jpg->found = 1;

        // create a new file name
        sprintf(jpg->name, "%03d.jpg", jpg->picture);
        printf("recovered %s\n", jpg->name);
        jpg->picture ++;
    }

    // as long as this is set apend the blocks to the file
    // this will allow for skipping over the junk until the
    // correct pattern is found
    if (jpg->found == 1)
    {
        rtv = writeBlock(jpg);
    }
    return rtv;
}

int main(int argc, char *argv[])
{
    int rtv = -10;
    JPEG jpg;
    char *msg;
    FILE *in = NULL;

    rtv = (argc == 2) ? SUCCESS : ERR_NO_ARG;
    if (rtv == SUCCESS)
    {
        // open the forensic file with the jpeg data
        in = fopen(argv[1], "r");
        rtv = (in == NULL) ? ERR_OPEN_CARD_FILE : SUCCESS;
    }

    // if able to open card.raw file
    if (rtv == SUCCESS)
    {
        // initialize jpeg structure
        jpg.block = calloc(sizeof(byte), BLOCK_SIZE + 0x10);
        jpg.picture = 0;
        jpg.found = 0;

        if (jpg.block)
        {
            // read and process the blcoks of data until eof or an error occurs
            do
            {
                rtv = readBlock(in, &jpg);
                switch (rtv)
                {
                    case SUCCESS:
                        rtv = process_block(&jpg);
                        break;
                    default:
                        break;
                }
            }
            while (rtv == SUCCESS || rtv == NOP);
            fclose(in);
            free(jpg.block);
        }
        else
        {
            rtv = ERR_NO_MEM;
        }
    }

    // print out error msg
    switch (rtv)
    {
        case ERR_NO_ARG:
            msg = "NO input file to process, usage : recover infile.raw";
            break;
        case ERR_NO_MEM:
            msg = "insufficient memory to perform operation";
            break;
        case ERR_OPEN_CARD_FILE:
            msg = "unable to open card file";
            break;
        case ERR_READ_CARD_FILE:
            msg = "read error in card file";
            break;
        case ERR_OPEN_JPG_FILE:
            msg = "unable to create or open jpeg file";
            break;
        case ERR_WRITE_JPG_FILE:
            msg = "write error in jpeg file";
            break;
        case ERR_EXCEPTION:
            msg = "unknown exception in proccess_block";
            break;
        default:
            msg = "finished";
            break;
    }

    fprintf(stderr, "%s\n", msg);
    return (rtv == FEOF) ? SUCCESS : rtv;
}

