#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Struc definition
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check argument validity
    if (argc != 2)
    {
        printf("Wrong arg\n");
        return 1;
    }
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Variable definition
    BYTE buffer[512];
    int counter = 0;
    char name[16];
    FILE *filename = NULL;
    filename = fopen("000.jpg", "w");

    // Scan the file to find JPG signatures
    while (fread(buffer, sizeof(BYTE) * 512, 1, inptr) == 1)
    {
        // If signature, create a file with custom name and write until next signature is found.
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            fclose(filename);
            printf("Signature sequence found\n");
            sprintf(name, "%03d.jpg", counter);
            printf("Filename is: %s\n", name);
            filename = fopen(name, "w");
            fwrite(buffer, sizeof(BYTE) * 512, 1, filename);
            counter += 1;
        }
        else if (counter != 0)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, filename);
        }
    }
    // Close the files.
    fclose(filename);
    fclose(inptr);
    return 0;
}