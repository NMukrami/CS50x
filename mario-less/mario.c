#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // print row
    for (int i = 0; i < height; i++)
    {
        // print space
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // print column
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // print new line command-line
        printf("\n");
    }
}