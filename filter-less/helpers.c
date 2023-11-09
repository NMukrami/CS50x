#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // convert to float for pixel
            float red_color = image[x][y].rgbtRed;
            float green_color = image[x][y].rgbtGreen;
            float blue_color = image[x][y].rgbtBlue;

            // get avg value
            int gray = round((red_color + green_color + blue_color) / 3);

            image[x][y].rgbtRed = gray;
            image[x][y].rgbtGreen = gray;
            image[x][y].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // convert to float
            float originalRed = image[x][y].rgbtRed;
            float originalGreen = image[x][y].rgbtGreen;
            float originalBlue = image[x][y].rgbtBlue;

            // get avg value and update the value of red
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            image[x][y].rgbtRed = fmin(255, sepiaRed);

            // get avg value and update the value of green
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            image[x][y].rgbtGreen = fmin(255, sepiaGreen);

            // get avg value and update the value of blue
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            image[x][y].rgbtBlue = fmin(255, sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // witdh devide by 2
    int width_2 = width / 2;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width_2; y++)
        {
            RGBTRIPLE temp_image = image[x][y];

            // swap pixel in image
            image[x][y] = image[x][width - y - 1]; // sawp pixels

            image[x][width - y - 1] = temp_image;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE t[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            t[x][y].rgbtRed = image[x][y].rgbtRed;
            t[x][y].rgbtGreen = image[x][y].rgbtGreen;
            t[x][y].rgbtBlue = image[x][y].rgbtBlue;
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int red_color, green_color, blue_color;
            red_color = green_color = blue_color = 0;
            float total = 0.00;

            // get the neighboring pixels
            for (int row = -1; row < 2; row++)
            {
                for (int column = -1; column < 2; column++)
                {
                    int h = x + row;
                    int w = y + column;
                    // check neighboring pixels valid or not
                    if (h > (height - 1) || h < 0 || w < 0 || w > (height - 1))
                    {
                        continue;
                    }
                    // get value img
                    red_color += image[h][w].rgbtRed;
                    green_color += image[h][w].rgbtGreen;
                    blue_color += image[h][w].rgbtBlue;
                    total++;
                }
            }
            // get avg pixel value
            t[x][y].rgbtRed = round(red_color / total);
            t[x][y].rgbtGreen = round(green_color / total);
            t[x][y].rgbtBlue = round(blue_color / total);
        }
    }

    // get a copy of new pixels to original img
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = t[x][y];
        }
    }
    return;
}
