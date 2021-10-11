#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{

    float change;

    do
    {
        // Prompt the user for the change owed
        change = get_float("Change owed: ");

    }
    while (change < 0);

    // Converts the amount to cents
    int cents =  round(change * 100);

    int coins = 0;
    int result = 0;

    do
    {
        // Test for Quarters
        if (cents >= 25)
        {
            result = cents / 25;
            cents %= 25;
        }
        // Test for Dimes
        else if (cents >= 10)
        {
            result = cents / 10;
            cents %= 10;
        }
        // Test for Nickles
        else if (cents >= 5)
        {
            result = cents / 5;
            cents %= 5;
        }
        // Test for Pennies
        else if (cents >= 1)
        {
            result = cents / 1;
            cents %= 1;
        }

        // Add up the used coins to the total
        coins += result;

    }
    while (cents > 0);

    printf("%i\n", coins);

}