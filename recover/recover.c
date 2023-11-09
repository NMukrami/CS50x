#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void argv_checker(int argc);
void file_checker(FILE *input_file);

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check argv valid or not
    argv_checker(argc);

    BYTE buffer[BLOCK_SIZE];

    // open file
    FILE *raw_file = fopen(argv[1], "r");

    char *filename = malloc(8 * sizeof(char));

    // pointer file
    FILE *output_file = NULL;

    // check the input_file is valid or not
    file_checker(raw_file);

    int counter_img = 0;

    // loop and read file block of 512
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // check bytes if block start of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter_img > 0)
            {
                fclose(output_file);
            }

            // open jpeg file
            sprintf(filename, "%03i.jpg", counter_img); // write jpeg filename
            output_file = fopen(filename, "w");         // open output_file and write it

            if (output_file == NULL)
            {
                fclose(raw_file);
                return 3;
            }
            counter_img++; // increment by 1
        }

        if (output_file != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output_file);
        }
    }
    // close file
    fclose(output_file);
    fclose(raw_file);
    free(filename);
    return 0;
}

// fun for argv command-line
void argv_checker(int argc)
{
    if (argc != 2)
    {
        printf("Invalid command-line argument\n");
        exit(1);
    }
}


// fun for file input
void file_checker(FILE *input_file)
{
    if (input_file == NULL)
    {
        printf("File not found\n");
        exit(2);
    }
}
