#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_letter(string text);
int get_word(string text);
int get_sentence(string text);

int main(void)
{
    // get user input
    string text = get_string("Text: ");

    // variable
    float letters = get_letter(text);
    float words = get_word(text);
    float sentences = get_sentence(text);

    // do some math calculation
    float L = letters / (words + 1) * 100;
    float S = sentences / (words + 1) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    // print the result
    if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else if (grade > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", grade);
    }
    printf("\n");
}

// check alphabet in text
int get_letter(string text)
{
    float letter = 0;

    for (int index = 0, len = strlen(text); index < len; index++)
    {

        if (isalpha(text[index]))
        {
            letter++;
        }
    }
    return letter;
}

// check whitespace in text
int get_word(string text)
{
    float word = 0;

    for (int index = 0, len = strlen(text); index < len; index++)
    {

        if (text[index] == ' ')
        {
            word++;
        }
    }
    return word;
}

// check symbol in text
int get_sentence(string text)
{
    float sentence = 0;

    for (int index = 0, len = strlen(text); index < len; index++)
    {

        if (text[index] == '!' || text[index] == '?' || text[index] == '.')
        {
            sentence++;
        }
    }
    return sentence;
}
