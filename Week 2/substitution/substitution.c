#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Function Declarations
int input_validation(int argc, string argv[]);
bool is_key_valid(string key);
string ciphertext(string plaintext, string key);


// Encrypt messages using the provided key
int main(int argc, string argv[])
{
    // Validate the command-line arguments
    int rc = input_validation(argc, argv);

    if (rc == 0)
    {
        // Validate if the key has 26 unique alpha characters
        if (is_key_valid(argv[1]))
        {
            // define the key
            string key = argv[1];

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
            return 1;
        }

    }
    else
    {
        // Alert the user about the correct usage
        printf("Usage: ./substitution key\n");
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
        return 0;
    }

}

// Validate the provided cipher key
bool is_key_valid(string key)
{
    // check if the key has 26 chars
    if (strlen(key) == 26)
    {
        // check if the key is all numeric and has no repeated characters
        bool alpha[26] = {false};
        int pos;

        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (! isalpha(key[i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return false;
            }

            pos = (int) toupper(key[i]) - 'A';
            if (! alpha[pos])
            {
                alpha[pos] = true;
            }
            else
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }

        return true;

    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

}


// Cipher the message using the provided key
string ciphertext(string plaintext, string key)
{

    string cipher = plaintext;
    int pos;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isalpha(c))
        {
            if (isupper(c))
            {
                pos = (int) c - 'A';
                cipher[i] = toupper(key[pos]);
            }
            else
            {
                pos = (int) c - 'a';
                cipher[i] = tolower(key[pos]);
            }

        }
        else
        {
            cipher[i] = c;
        }

        // printf("%i: %c -> %c\n", i, c, cipher[i]);
    }

    return cipher;

}