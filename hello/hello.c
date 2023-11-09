#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // ask user name
    string name = get_string("What is your name?\n");

    // print user name
    printf("hello, %s\n", name);
}