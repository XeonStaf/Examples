#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#pragma pack(push, 1)
struct bmpHeader
{
    uint16_t bfType; //2
    uint32_t bfileSize; //4
    uint32_t bfReserved; //4
    uint32_t bOffBits; //4
    uint32_t biSize; //4
    uint32_t biWidth; //4
    uint32_t biHeight; //4
    uint16_t biPlanes; //2
    uint16_t biBitCount; //2
    uint32_t biCompression; //4
    uint32_t biSizeImage; //4
    uint32_t biXPelsPerMeter; //4
    uint32_t biYPelsPerMeter; //4
    uint32_t biClrUsed; // 4
    uint32_t biClrImportant; //4
};

#pragma pack(pop)

struct pixel
{
    uint8_t b, g, r;
};

struct image
{
    uint64_t width, height;
    struct pixel *data;
};

enum read_status
{
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_NAME,
    READ_SIZE_LIMIT
};

enum write_status
{
    WRITE_OK = 0,
    WRITE_INVALID_NAME,
    WRITE_NO_IMAGE
};

enum read_status fromBmp(FILE*, struct image*);
enum write_status toBmp(FILE*, struct image const*);
