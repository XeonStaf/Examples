#include "rotate.h"
#pragma once

struct image rotate(struct image const source, uint32_t angle)
{
    struct image newImage;
    const struct pixel White = {255, 255, 255};

    size_t i, j, newi, newj;
    double_t sinphi = sin(angle / 180 * M_PI);
    double_t cosphi = cos(angle / 180 * M_PI);

    newImage.width = source.width;
    newImage.height = source.height;
    newImage.data = malloc(sizeof(struct pixel) * newImage.width * newImage.height);
    for (size_t p = 0; p < source.width * source.height; p++)
        newImage.data[p] = White;

    for (size_t p = 0; p < source.width * source.height; p++)
    {
        i = p / source.height;
        j = p - (p / source.height * source.height);
        newi = j * cosphi + i * sinphi;
        newj = i * cosphi - j * sinphi;
        if (newi * source.height + newj < source.height * source.width)
            newImage.data[newi * source.height + newj] = source.data[p];
    }
    return newImage;
}