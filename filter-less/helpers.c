#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Pixel average calculation
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Pixel replacement with average value
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For each pixel apply sepia filter calculation
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);


            // If value > 255, it will be equal to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Pixel replacement
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE(*buffer)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Fior each pixel, put it in buffer and at the end for row.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            buffer[i][width - j - 1] = image[i][j];
        }
    }

    // Pixel replacement output image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }
    free(buffer);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*copy)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));

    int count = 0;

    // For each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = 0;
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    // Scan adjacent pixels if they exist
                    int m = i + k;
                    int n = j + l;
                    if (((m >= 0) && (n >= 0)) && ((m < height) && (n < width)))
                    {
                        // Calculate the sum for each colors for each adjacent pixel
                        sum_red = sum_red + image[m][n].rgbtRed;
                        sum_green = sum_green + image[m][n].rgbtGreen;
                        sum_blue = sum_blue + image[m][n].rgbtBlue;
                        count += 1;
                    }
                    else
                    {
                        count += 0;
                    }
                }
            }

            // Calcul the average and copy it in buffer image to avoid conflict
            copy[i][j].rgbtRed = round(sum_red / count);
            copy[i][j].rgbtGreen = round(sum_green / count);
            copy[i][j].rgbtBlue = round(sum_blue / count);
        }
    }
    // Output image pixel replacement
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    free(copy);
    return;
}