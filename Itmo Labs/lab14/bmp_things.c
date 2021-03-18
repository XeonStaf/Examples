#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
#pragma pack(1)

typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;  
    unsigned long bfSize;  
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;  
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned long biSize; 
    long biWidth; 
    long biHeight;  
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long biCompression;
    unsigned long biSizeImage;  
    long biXPelsPerMeter;  
    long biYPelsPerMeter;  
    unsigned long biClrUsed;
    unsigned long biClrImportant;
}BITMAPINFOHEADER;

char *toString(int x)
{
    char *res;
    int x_cpy = x;
    int n = 0;
    while(x_cpy > 0)
    {
        x_cpy = x_cpy / 10;
        n++;
    }
    res = malloc(sizeof(char) * n);
    for(int i = n - 1; i >= 0; i--)
    {
        res[i] = (char) (x % 10) + '0';
        x /= 10;
    }
    res[n] = '\0';
    return res;
}

int lenght(char a[])
{
    int i = 0;
    while(a[i] != '\0')
    i++;
    return i;
}

unsigned char *LoadBMP(char *filename, BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader)
{
    FILE *filePtr;
    unsigned char *bitmapImage; 
    int imageIdx = 0; 
    unsigned char tempRGB;  

    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr); 
    fseek(filePtr, bitmapFileHeader -> bfOffBits, SEEK_SET);

    int N = bitmapInfoHeader -> biWidth * bitmapInfoHeader -> biHeight * 3;
    bitmapImage = malloc(sizeof(unsigned char) * N);
    fread(bitmapImage,sizeof(unsigned char), N, filePtr);

    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    unsigned char* New = malloc(sizeof(unsigned char) * N / 3);
    int count = 0;

    for (imageIdx = 0;imageIdx < N;imageIdx+=3) 
    {
        if (bitmapImage[imageIdx] + bitmapImage[imageIdx + 1] + bitmapImage[imageIdx + 2] == 765)
            New[count] = 255;
        else
            New[count] = 0;
        count ++;
    }
    fclose(filePtr);
    return New;
}


void CreateBMP(unsigned char* Game, int N, char* filename, char* output_dir, int iteration, BITMAPINFOHEADER *bitmapInfoHeader, BITMAPFILEHEADER *bitmapFileHeader)
{   
    
    char newfilename[200];
    char *iter;
    iter = toString(iteration);
    strncat(newfilename, filename, 20);
    strncat(newfilename, "_", 2);
    strncat(newfilename, iter, 5);
    strncat(newfilename, ".bmp", 5);
    FILE* output = fopen(newfilename, "wb");
    output = fopen(newfilename, "wb");

    fwrite(&bitmapFileHeader -> bfType, sizeof(bitmapFileHeader -> bfType), 1, output);
    fwrite(&bitmapFileHeader -> bfSize, sizeof(bitmapFileHeader -> bfSize), 1, output);
    fwrite(&bitmapFileHeader -> bfReserved1, sizeof(bitmapFileHeader -> bfReserved1), 1, output);
    fwrite(&bitmapFileHeader -> bfReserved2, sizeof(bitmapFileHeader -> bfReserved2), 1, output);
    fwrite(&bitmapFileHeader -> bfOffBits, sizeof(bitmapFileHeader -> bfOffBits), 1, output);
    fwrite(&bitmapInfoHeader -> biSize, sizeof(bitmapInfoHeader -> biSize), 1, output);
    fwrite(&bitmapInfoHeader -> biWidth, sizeof(bitmapInfoHeader -> biWidth), 1, output);
    fwrite(&bitmapInfoHeader -> biHeight, sizeof(bitmapInfoHeader -> biHeight), 1, output);
    fwrite(&bitmapInfoHeader -> biPlanes, sizeof(bitmapInfoHeader -> biPlanes), 1, output);
    fwrite(&bitmapInfoHeader -> biBitCount, sizeof(bitmapInfoHeader -> biBitCount), 1, output);
    fwrite(&bitmapInfoHeader -> biCompression, sizeof(bitmapInfoHeader -> biCompression), 1, output);
    fwrite(&bitmapInfoHeader -> biSizeImage, sizeof(bitmapInfoHeader -> biSizeImage), 1, output);
    fwrite(&bitmapInfoHeader -> biXPelsPerMeter, sizeof(bitmapInfoHeader -> biXPelsPerMeter), 1, output);
    fwrite(&bitmapInfoHeader -> biYPelsPerMeter, sizeof(bitmapInfoHeader -> biYPelsPerMeter), 1, output);
    fwrite(&bitmapInfoHeader -> biClrUsed, sizeof(bitmapInfoHeader -> biClrUsed), 1, output);
    fwrite(&bitmapInfoHeader -> biClrImportant, sizeof(bitmapInfoHeader -> biClrImportant), 1, output);
    for(int i = 0; i < N; i++)
    {
        putc(Game[i], output);
        putc(Game[i], output);
        putc(Game[i], output);
    }
    fclose(output);
}