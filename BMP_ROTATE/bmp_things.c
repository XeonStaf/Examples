#include "bmp_things.h"
#pragma once


enum read_status fromBmp(FILE *in, struct image *img) 
{
    struct bmpHeader Header;
    fread(&Header, sizeof(Header), 1, in);
    fseek(in, Header.bOffBits, SEEK_SET);

    if (Header.bfType != 0x4D42)
        return READ_INVALID_SIGNATURE;
    if (Header.biBitCount != 24)
        return READ_INVALID_BITS;
    if (Header.bfileSize - Header.biSizeImage != Header.bOffBits)
        return READ_INVALID_HEADER;
    if (Header.biWidth * Header.biHeight > 4294967296)
        return READ_SIZE_LIMIT;

    struct pixel onepixel;
    img -> width = Header.biWidth;
    img -> height = Header.biHeight;
    img -> data = malloc(sizeof(struct pixel) * img -> width * img -> height);

    for (size_t i = 0; i < img -> height; i++)
    {
        for (size_t j = 0; j < img -> width; j++)
        {
            fread(&onepixel, sizeof(struct pixel), 1, in);
            img->data[i * (img->height) + j] = onepixel;
        }
        fseek(in, img->width % 4, SEEK_CUR);
    }

    return 0;
}


enum write_status toBmp(FILE *out, struct image const *img)
{
    if (out == NULL)
        return WRITE_INVALID_NAME;
    if (img == NULL)
        return WRITE_NO_IMAGE;
    struct bmpHeader Header;

    Header.bfType = 0x4D42;
    Header.biWidth = img -> width;
    Header.biHeight = img -> height;
    Header.bfileSize = Header.biWidth * Header.biHeight * 3 + sizeof(Header);
    Header.biSize = 40;
    Header.bOffBits = sizeof(struct bmpHeader);
    Header.biPlanes = 1;
    Header.biBitCount = 24;
    Header.bfReserved = 0;
    Header.biCompression = 0;
    Header.biSizeImage = Header.biWidth * Header.biHeight * 3;
    Header.biXPelsPerMeter = 0;
    Header.biYPelsPerMeter = 0;
    Header.biClrUsed = 0;
    Header.biClrImportant = 0;

    struct pixel *pixels;
    fwrite(&Header, sizeof(Header), 1, out);
    for (size_t i = 0; i < img->height; i++)
    {
        for (size_t j = 0; j < img->width; j++)
            fwrite(&(img->data[i * (img->height) + j]), sizeof(struct pixel), 1, out);
        fseek(out, img->width % 4, SEEK_CUR);
    }
    return 0;

}
