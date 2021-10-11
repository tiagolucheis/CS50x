#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Function Declarations
int input_validation(int argc, string argv[]);
string ciphertext(string plaintext, int key);


// Encrypt messages using Caesar's cipher
int main(int argc, string argv[])
{
    // Validate the command-line arguments
    int rc = input_validation(argc, argv);

    if (rc == 0)
    {
        // define the key
        int key = atoi(argv[1]);

        // Get user message
        string msg = get_string("plaintext: ");

        // Cipher the message
        string cipher = ciphertext(msg, key);

        // Print the ciphertext
        printf("ciphertext: %s\n", cipher);
        return rc;
    }
    else
    {
        // Alert the user about the correct usage
        printf("Usage: ./caesar key\n");
        return rc;
    }

}


// Validate command-line arguments
int input_validation(int argc, string argv[])
{
    // check for single argument
    if (argc != 2)
    {
        return 1;
    }
    else
    {
        // check if the key is all numeric
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                return 1;
            }
        }
    }

    return 0;

}


// Cipher the message using the provided key
string ciphertext(string plaintext, int key)
{

    string cipher = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        if (isupper(c))
        {
            cipher[i] = ((c - 'A' + key) % 26) + 'A';
        }
        else if (islower(c))
        {
            cipher[i] = ((c - 'a' + key) % 26) + 'a';
        }
        else
        {
            cipher[i] = c;
        }

        printf("%i: %c -> %c\n", i, c, cipher[i]);
    }

    return cipher;

}