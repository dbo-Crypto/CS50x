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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

//declaration of temp image
    RGBTRIPLE copy[height][width];

//Declaration of Gx and Gy variables.
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


//For each piwel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_red = 0;
            int Gx_green = 0;
            int Gx_blue = 0;
            int Gy_red = 0;
            int Gy_green = 0;
            int Gy_blue = 0;

// Scan adjacent pixels if they exist
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }

                    // Multiply each colors of each pixel by the Gx/Gy factor.
                    Gx_red += (image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1]);
                    Gx_green += (image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1]);
                    Gx_blue += (image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1]);
                    Gy_red += (image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1]);
                    Gy_green += (image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1]);
                    Gy_blue += (image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1]);
                }
            }
            //Apply Sobel formula
            int Sobel_red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int Sobel_green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int Sobel_blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            if (Sobel_red > 255)
            {
                Sobel_red = 255;
            }
            if (Sobel_green > 255)
            {
                Sobel_green = 255;
            }
            if (Sobel_blue > 255)
            {
                Sobel_blue = 255;
            }

            //Copy values in temp image
            copy[i][j].rgbtBlue = Sobel_blue;
            copy[i][j].rgbtGreen = Sobel_green;
            copy[i][j].rgbtRed = Sobel_red;
        }
    }

// Copy temp image to output
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
    return;
}
