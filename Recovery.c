#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the forensic image
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];     // 512-byte buffer
    FILE *img = NULL;               // pointer to current JPEG file
    int file_count = 0;             // number of JPEGs found
    char filename[8];               // e.g., "000.jpg"

    // Read the card block by block
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Check if block is start of a JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG was already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create new filename
            sprintf(filename, "%03i.jpg", file_count);
            file_count++;

            // Open new JPEG file
            img = fopen(filename, "w");
        }

        // If we are currently writing to a JPEG file, write the block
        if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Close last file if open
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}
