#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Number of bytes in FAT file system
const int BLOCK_SIZE = 512;

// Type definition
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{

    // Check if command was used correctly
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open raw file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // Create a buffer and open the file
    BYTE buffer[BLOCK_SIZE];
    char *filename = malloc(sizeof(char) * 8);
    int nImage = 0;

    // Create the First Image 000.jpg
    sprintf(filename, "%03i.jpg", nImage);

    FILE *image = fopen(filename, "w");
    if (image == NULL)
    {
        printf("Could not open file.\n");
        free(filename);
        return 3;
    }

    // Swipe the raw file and creates all the JPGs that can be detected
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file))
    {
        // Check for the beggining of a JPEG and creates a new file for it
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (nImage != 0)
            {
                fclose(image);
            }
            sprintf(filename, "%03i.jpg", nImage);
            image = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, image);
            nImage++;
        }
        // Write the contiguous block to the JPEG
        else
        {
            if (nImage != 0)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, image);
            }
        }
    }

    // Close files
    fclose(image);
    fclose(file);
    free(filename);
}