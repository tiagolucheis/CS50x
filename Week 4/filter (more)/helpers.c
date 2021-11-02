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
            image[i][j] = blurredImage[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a temp matrix to store the modified image
    RGBTRIPLE edgedImage[height][width];

    // Initialize the Gx and Gy kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Variables for Gx and Gy for each colour channel
    int redX, redY, greenX, greenY, blueX, blueY;
    int edgeRed, edgeGreen, edgeBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset the X and Y values
            redX = 0;
            redY = 0;
            greenX = 0;
            greenY = 0;
            blueX = 0;
            blueY = 0;

            for (int row = (i - 1), a = 0; row <= (i + 1); row++, a++)
            {
                for (int col = (j - 1), b = 0; col <= (j + 1); col++, b++)
                {
                    if (row >= 0 && row < height && col >=0 && col < width)
                    {
                        // Compute Gx for each colour channel
                        int multX = Gx[a][b];
                        redX += image[row][col].rgbtRed * multX;
                        greenX += image[row][col].rgbtGreen * multX;
                        blueX += image[row][col].rgbtBlue * multX;

                        // Compute Gy for each colour channel
                        int multY = Gy[a][b];
                        redY += image[row][col].rgbtRed * multY;
                        greenY += image[row][col].rgbtGreen * multY;
                        blueY += image[row][col].rgbtBlue * multY;
                    }
                }
            }

            // Combine Gx and Gy for each color channel
            edgeRed = round(sqrt(pow(redX, 2) + pow(redY, 2)));
            edgeGreen = round(sqrt(pow(greenX, 2) + pow(greenY, 2)));
            edgeBlue = round(sqrt(pow(blueX, 2) + pow(blueY, 2)));

            // Adjust exceeding values
            if (edgeRed > 255) edgeRed = 255;
            if (edgeGreen > 255) edgeGreen = 255;
            if (edgeBlue > 255) edgeBlue = 255;

            // Define the new Pixels for the Edged Image
            edgedImage[i][j].rgbtRed = edgeRed;
            edgedImage[i][j].rgbtGreen = edgeGreen;
            edgedImage[i][j].rgbtBlue = edgeBlue;

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Replace each pixel with its edged equivalent
            image[i][j] = edgedImage[i][j];
        }
    }

    return;
}