#include "helpers.h"
#include "stdio.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grayvalue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find the average value beteen pixel's RGB and set it as the gray value
            grayvalue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = grayvalue;
            image[i][j].rgbtGreen = grayvalue;
            image[i][j].rgbtBlue = grayvalue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define the sepia value for each color, based on the formula below:
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Adjust exceeding values
            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            // Attribute the sepia values to each color for that pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR, tempG, tempB;
    for (int i = 0; i < height; i++)
    {
        // Sweep only half of the image, swaping pixels from left to right
        for (int j = 0, r = width - 1; j < width / 2; j++, r--)
        {
            // Store left pixels at a temp variable
            tempR = image[i][j].rgbtRed;
            tempG = image[i][j].rgbtGreen;
            tempB = image[i][j].rgbtBlue;
            // Swap right pixels to the left
            image[i][j].rgbtRed = image[i][r].rgbtRed;
            image[i][j].rgbtGreen = image[i][r].rgbtGreen;
            image[i][j].rgbtBlue = image[i][r].rgbtBlue;
            // Place the stored left pixels to the right
            image[i][r].rgbtRed = tempR;
            image[i][r].rgbtGreen = tempG;
            image[i][r].rgbtBlue = tempB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temp matrix to store the modified image
    RGBTRIPLE blurredImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int nPixels = 0;
            float sumRed = 0, sumGreen = 0, sumBlue = 0;

            for (int row = (i - 1); row <= (i + 1); row++)
            {
                for (int col = (j - 1); col <= (j + 1); col++)
                {
                    if (row >= 0 && row < height && col >=0 && col < width)
                    {
                        // Account the number of pixels and the sum of RGB values
                        sumRed += image[row][col].rgbtRed;
                        sumGreen += image[row][col].rgbtGreen;
                        sumBlue += image[row][col].rgbtBlue;
                        nPixels++;
                    }
                }
            }
            // Define the blurred pixels based on the average of their surrounding values
            blurredImage[i][j].rgbtRed = round(sumRed / nPixels);
            blurredImage[i][j].rgbtGreen = round(sumGreen / nPixels);
            blurredImage[i][j].rgbtBlue = round(sumBlue / nPixels);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Replace each pixel with its blurred equivalent
            image[i][j].rgbtRed = blurredImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurredImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurredImage[i][j].rgbtBlue;
        }
    }

    return;
}
