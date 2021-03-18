#include "bmp_things.c"

int NextState(unsigned char *bitmapData, int size, int width, int i)
{
    int neighbour[8];
    neighbour[0] = i - width;
    neighbour[1] = i + width;
    neighbour[2] = i + 1;
    neighbour[3] = i - 1;
    neighbour[4] = i + 1 + width;
    neighbour[5] = i + 1 - width;
    neighbour[6] = i - 1 + width;
    neighbour[7] = i - 1 - width;

    int alive = 0;
    for(int i = 0; i < 8; i++)
        if (neighbour[i] >= 0 && neighbour[i] < size)
            if(bitmapData[neighbour[i]] == 0)
                alive++;
            
    if ((bitmapData[i] != 0 && alive == 3) || (bitmapData[i] == 0 && alive > 1 && alive < 4))
        return 0;
    return 255;
}

unsigned char* gametick(unsigned char *bitmapData, BITMAPINFOHEADER bitmapInfoHeader)
{
    int N = bitmapInfoHeader.biHeight *  bitmapInfoHeader.biWidth;;
    unsigned char* New = malloc(sizeof(unsigned char) * N);
    int pos;
    for(int i = 0; i < N; i++)
        New[i] = NextState(bitmapData, N, bitmapInfoHeader.biWidth, i);
    return New;
}