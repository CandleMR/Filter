#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      float f = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
       f = round(f / 3.0);
      image[i][j].rgbtRed = f;
      image[i][j].rgbtGreen = f;
      image[i][j].rgbtBlue = f;
}}return;}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
   RGBTRIPLE temp;
    for(int i = 0; i < height; i++){
    for(int j = 0; j <  width / 2; j++){
          temp =  image[i][j];
             image[i][j] = image[i][width - j - 1];
                  image[i][width - j - 1] = temp;
}}return;}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
             for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    temp[i][j] = image[i][j];
                }}

             for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    int R = 0;
                    int G = 0;
                    int B = 0;
                    float counter = 0;
            for(int c = -1; c <= 1; c++){
            for(int k = -1; k <= 1; k++){
                if(i + c >= 0 && i + c < height && j + k >= 0 && j + k < width){
                     R += temp[i + c][j + k].rgbtRed;
                     B += temp[i + c][j + k].rgbtBlue;
                     G += temp[i + c][j + k].rgbtGreen;
                     counter++;
                    }}}

                     image[i][j].rgbtRed = round(R / counter);
                     image[i][j].rgbtBlue = round(B / counter);
                     image[i][j].rgbtGreen = round(G / counter);
        }}
        return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
        int Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
};

        int Gy[3][3] = {
            {-1, -2, -1},
            { 0,  0,  0},
            { 1,  2,  1}
};
                 for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                   float red_Gx = 0, red_Gy = 0;
                   float blue_Gx = 0, blue_Gy = 0;
                   float green_Gx = 0, green_Gy = 0;
                   for(int c = -1; c <= 1; c++){
                    for(int k = -1; k <= 1; k++){
                    if(i + c >= 0 && i + c < height && j + k >= 0 && j + k < width){
            int R = image[i + c][j + k].rgbtRed;
            red_Gx += R * Gx[c + 1][k + 1];
             int B = image[i + c][j + k].rgbtBlue;
              blue_Gx += B * Gx[c + 1][k + 1];
              int G = image[i + c][j + k].rgbtGreen;
              green_Gx += G * Gx[c + 1][k + 1];
              red_Gy += R * Gy[c + 1][k + 1];
              green_Gy += G * Gy[c + 1][k + 1];
              blue_Gy  += B * Gy[c + 1][k + 1];
                }}}
            int total_red = round(sqrt(pow(red_Gx, 2) + pow(red_Gy, 2)));
             int total_blue = round(sqrt(pow(blue_Gx, 2) + pow(blue_Gy, 2)));
              int total_green = round(sqrt(pow(green_Gx, 2) + pow(green_Gy, 2)));
              if (total_red > 255) total_red = 255;
              if (total_green > 255) total_green = 255;
              if (total_blue > 255) total_blue = 255;
              copy[i][j].rgbtRed = total_red;
              copy[i][j].rgbtGreen = total_green;
              copy[i][j].rgbtBlue = total_blue;
            }
        }
            for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
