// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t buffer[HEADER_SIZE + 1];
    int16_t data;
    int cnt = 0;

    // TODO: Copy header from input file to output file
    cnt = fread(buffer, sizeof(uint8_t), HEADER_SIZE, input);
    if (cnt == HEADER_SIZE)
    {
        fwrite(buffer, sizeof(uint8_t), HEADER_SIZE, output);
        // TODO: Read samples from input file and write updated data to output file
        do
        {
            cnt = fread(&data, sizeof(int16_t), 1, input);
            data = (int16_t)((float)(data) * factor);
            fwrite(&data, sizeof(int16_t), cnt, output);
        }
        while (!feof(input));
    }
    // Close files
    fclose(input);
    fclose(output);
}
