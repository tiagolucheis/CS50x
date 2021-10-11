#include <math.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Function Declarations
int text_index(string text);
void count(string text, int *letters, int *words, int *sentences);
int is_letter(char c);
int is_space(char c);
int is_punctuation(char c);

// Return the Coleman-Liau index of a given Text
int main(void)
{
    // Get input text for scoring
    string text = get_string("Text: ");

    // Calculate the grade
    int grade = text_index(text);

    // Print the Grade
    if (grade >= 16)
    {
        printf("Grade 16+");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", grade);
    }
    printf("\n");

}

// Calculate the Coleman-Liau index of a given Text
int text_index(string text)
{
    // Count Letters, Words and Sentences
    int letters = 0, words = 0, sentences = 0;
    count(text, &letters, &words, &sentences);

    // Calculate the Index
    float L = letters / (float) words * 100;
    float S = sentences / (float) words * 100;
    int index = (int) round((0.0588 * L) - (0.296 * S) - 15.8);

    return index;
}

// Count the number of Letters, Words and Sentences of a Text
void count(string text, int *letters, int *words, int *sentences)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (is_letter(text[i]))
        {
            (*letters)++;
        }
        else if (is_space(text[i]))
        {
            (*words)++;
        }
        else if (is_punctuation(text[i]))
        {
            (*sentences)++;
        }
    }

    (*words)++;

}

// Check if a character correspond to a Letter from A to Z
int is_letter(char c)
{
    if (toupper(c) >= 'A' && toupper(c) <= 'Z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if a character correspond to a space
int is_space(char c)
{
    if (c == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if a character correspond to a punctuation sign
int is_punctuation(char c)
{
    if (c == '.' || c == '!' || c == '?')
    {
        return true;
    }
    else
    {
        return false;
    }
}