#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // get user input
    string msg_user = get_string("Message: ");

    int binary_array[BITS_IN_BYTE];

    // loop each chart in string
    for (int i = 0, len = strlen(msg_user); i < len; i++)
    {
        // convert char to ASCII
        int decimal = msg_user[i];

        for (int x = BITS_IN_BYTE - 1; x >= 0; x--)
        {
            // fill in binary array
            binary_array[x] = decimal % 2;
            decimal /= 2;
        }
        // print binary
        for (int n = 0; n < BITS_IN_BYTE; n++)
        {
            print_bulb(binary_array[n]);
        }
        // new line
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
