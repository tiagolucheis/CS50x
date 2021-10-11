#include <stdio.h>
#include <math.h>
#include <cs50.h>

// Check_Card compile declaration
string check_Card(long number);

int main(void)
{

    long cardNumber;

    do
    {
        // Prompt the user for the Card Number
        cardNumber = get_long("Number: ");

    }
    while (cardNumber < 0);

    // Check if the number is a valid Credit Card and prints its Banner
    printf("%s\n", check_Card(cardNumber));

}

// Check if the number is valid and returns its Banner or an Invalid message
string check_Card(long number)
{
    int nDigits = floor(log10(number)) + 1;
    string check;

    // checks if it is within the accepted range
    if (nDigits >= 13 && nDigits <= 16)
    {

        long num = number;

        int digit = 0, sum = 0;

        for (int i = 1; i <= nDigits; i++)
        {
            digit = num % 10;
            num = (num - digit) / 10;

            if (i % 2 == 0)
            {
                if ((digit * 2) / 10 > 0)
                {
                    int d = digit * 2;
                    sum += (d / 10) + (d % 10);
                }
                else sum += digit * 2;
            }
            else sum += digit;


        }

        if (sum % 10 == 0)
        {

            int init;
            long power = pow(10, (nDigits - 1));

            init = number / power;
            if (init == 3 || init == 5) init = (init * 10) + ((number - init * power) / (power / 10));

            switch (init)
            {
                case 4:
                    check = "VISA";
                    break;
                case 34:
                    check = "AMEX";
                    break;
                case 37:
                    check = "AMEX";
                    break;
                case 51:
                case 55:
                    check = "MASTERCARD";
                    break;
                default:
                    check = "INVALID";
            }
        }
        else check = "INVALID";

    }
    else check = "INVALID";

    return check;
}