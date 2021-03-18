#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_things.c"
#include "game.c"

int main(int argc, char *argv[])
{
    char filename[100];
    char output_dir[200];
    int freq = 10;
    int count = 0;
    int max_iter = 1000;
    int alive, k;
    BITMAPINFOHEADER bitmapInfoHeader;
    BITMAPFILEHEADER bitmapFileHeader; 
    unsigned char *Game, *New;
    for(int i = 1; i < argc; i++)
    {
        if (argv[i][2] == 'i')
            strncpy(filename, argv[i + 1], 100);
        if (argv[i][2] == 'o')
            strncpy(output_dir, argv[i + 1], 200);            
        if (argv[i][2] == 'm')
        {
            max_iter = 0; k = 1;
            for(int j = lenght(argv[i + 1]) - 1; j >= 0; j--)
                {
                    max_iter += (argv[i + 1][j] - '0') * k;
                    k = k * 10;
                }
        }
        if (argv[i][2] == 'd')
        {
            freq = 0; k = 1;
            for(int j = lenght(argv[i + 1]) - 1; j >= 0; j--)
                {
                    freq += (argv[i + 1][j] - '0') * k;
                    k = k * 10;
                }
        }        
    }

    printf("Filename: %s\nMax Iteration: %d\nFrequency: %d", filename, max_iter, freq);
    Game = LoadBMP(filename, &bitmapInfoHeader, &bitmapFileHeader);

    int Size = bitmapInfoHeader.biHeight *  bitmapInfoHeader.biWidth;
    while(count < max_iter)
    {
        New = gametick(Game, bitmapInfoHeader);
        if (count % freq == 0)
            CreateBMP(New, Size, "Game", *output_dir, count, &bitmapInfoHeader, &bitmapFileHeader);
        count++;
        alive = 0;
        for(int i = 0; i < Size; i++)
        {
            Game[i] = New[i];
            if (New[i] = 255) 
            alive++;
        }
        if(alive == 0)
            break;
            

    }
    printf("\nDONE!");
    return 0;
}