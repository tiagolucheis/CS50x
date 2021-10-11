#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt for the Height
    do
    {

        height = get_int("Height: ");

    }
    while (height < 1 || height > 8);

    // Print all Rows
    for (int row = 0; row < height; row++)
    {
        // Print the spaces to right-align the pyramid
        for (int dot = 0; dot < height - row - 1; dot++)
        {
            printf(" ");
        }

        // Print the right-aligned pyramid
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }

        // Print the gap between pyramids
        printf("  ");

        // Print the left-aligned pyramid
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }

        // Print a newline for next pyramid level
        printf("\n");
    }
}