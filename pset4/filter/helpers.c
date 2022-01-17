// helpers.c
// cs50
// k.r.bergerstock
// @ 2020.11.19

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

BYTE average(int sum, int n)
{
    double r = (double)sum / (double) n + 0.5;
    return (BYTE) r;
}


// Convert image to grayscale
// operation can be done in place
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    int gs = 0;
    for (int h = 0; h < height; h++)
        for (int w = 0; w < width; w++)
        {
            pixel = image[h][w];
            gs = (int)pixel.rgbtBlue;
            gs += (int)pixel.rgbtGreen;
            gs += (int)pixel.rgbtRed;
            gs = average(gs, 3);
            pixel.rgbtBlue = (BYTE)gs;
            pixel.rgbtGreen = (BYTE)gs;
            pixel.rgbtRed = (BYTE)gs;
            image[h][w] = pixel;
        }
}

// Reflect image horizontally
// operatoiion can be done in place
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE p1, p2;
    int _width = width / 2;
    for (int h = 0; h < height; h++)
        for (int w = 0; w < _width; w++)
        {
            p1 = image[h][w];
            p2 = image[h][width - w - 1];
            image[h][w] = p2;
            image[h][width - w - 1] = p1;
        }

    return;
}

// Blur image
// must be down by making a copy
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for blurred image
    RGBTRIPLE(*nimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (nimage == NULL)
    {
        fprintf(stderr, "Not enough memory to perform operation.\n");
    }
    else
    {
        RGBTRIPLE pixel;
        int sb, sg, sr, x, y, n;
        const int lh[9] = {-1,-1,-1, 0, 0, 0, 1, 1, 1};
        const int lw[9] = {-1, 0, 1,-1, 0, 1,-1, 0, 1};

        for (int h = 0; h < height; h++)
            for (int w = 0; w < width; w++)
            {
                sb = sg = sr = n = 0;
                for (int i = 0; i < 9; i++)
                {
                    x = w + lw[i];
                    y = h + lh[i];
                    if (x >= 0 && y >= 0 && x < width && y < height)
                    {
                        pixel = image[y][x];
                        sb += (int)pixel.rgbtBlue;
                        sg += (int)pixel.rgbtGreen;
                        sr += (int)pixel.rgbtRed;
                        n++;
                    }
                }
                pixel.rgbtBlue = (BYTE)average(sb, n);
                pixel.rgbtGreen = (BYTE)average(sg, n);
                pixel.rgbtRed = (BYTE)average(sr, n);
                nimage[h][w] = pixel;
            }
        // overwrite original image with blurred image
        for (int h = 0; h < height; h++)
            for (int w = 0; w < width; w++)
            {
                image[h][w] = nimage[h][w];
            }
        free(nimage);
    }

}

// Detect edges
// musst be done by resullts being stored in a matrix
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int blue;
        int green;
        int red;
    } EDGE;

    // Allocate memory for edged derivitive results
    EDGE(*nimage)[width] = calloc(height, width * sizeof(EDGE));
    if (nimage == NULL)
    {
        fprintf(stderr, "Not enough memory to perform operation.\n");
    }
    else
    {
        RGBTRIPLE pixel;
        int sbx, sgx, srx;
        int sby, sgy, sry;
        int x, y;
        double sum, dxy;
        EDGE edge;

        // locatioon and  weights for kernalsl
        const int lh[9] = {-1,-1,-1, 0, 0, 1, 1, 1};
        const int lw[9] = {-1, 0, 1,-1, 1,-1, 0, 1};
        const int gx[9] = {-1, 0, 1,-2, 2,-1, 0, 1};
        const int gy[9] = {-1,-2,-1, 0, 0, 1, 2, 1};
        // cumalitve sum
        sum = 0.0;

        for (int h = 0; h < height; h++)
            for (int w = 0; w < width; w++)
            {
                sbx = sgx = srx = 0;
                sby = sgy = sry = 0;
                // perform the kernel operation
                for (int i = 0; i < 8; i++)
                {
                    y = h + lh[i];
                    x = w + lw[i];
                    if (x >= 0 && y >= 0 && x < width && y < height)
                    {
                        pixel = image[y][x];
                        sbx += gx[i] * (int)pixel.rgbtBlue;
                        sgx += gx[i] * (int)pixel.rgbtGreen;
                        srx += gx[i] * (int)pixel.rgbtRed;
                        sby += gy[i] * (int)pixel.rgbtBlue;
                        sgy += gy[i] * (int)pixel.rgbtGreen;
                        sry += gy[i] * (int)pixel.rgbtRed;
                    }
                }
                // calc and store results
                edge.blue = (int)(0.5 + sqrt(sbx * sbx + sby * sby)) ;
                edge.green = (int)(0.5 + sqrt(sgx * sgx + sgy * sgy));
                edge.red = (int)(0.5 + sqrt(srx * srx + sry * sry));
                nimage[h][w] = edge;
                sum += (double)edge.blue + (double)edge.green + (double)edge.red;
            }
        // scale the results so that the average luminence = 128
        // dxy = (sum / (double)(height * width * 3)) / 128.0;
        dxy = 1.0;
        // convert the results back to pixels anad overwiite original image
        for (int h = 0; h < height ; h++)
            for (int w = 0; w < width ; w++)
            {
                edge = nimage[h][w];
                pixel.rgbtBlue = dxy * edge.blue > 255 ? 255 : (BYTE)(dxy * edge.blue);
                pixel.rgbtGreen = dxy * edge.green > 255 ? 255 : (BYTE)(dxy * edge.green);
                pixel.rgbtRed = dxy * edge.red > 255 ? 255 : (BYTE)(dxy * edge.red);
                image[h][w] = pixel;
            }
    }
    free(nimage);
}
