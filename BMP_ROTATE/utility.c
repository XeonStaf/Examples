#include "utility.h"
uint32_t lenght(char *a)
{
    uint32_t i = 0;
    while (a[i] != '\0')
        i++;
    return i;
}

uint32_t strToint(char *str)
{
    uint32_t k = 1, result = 0;
    for (int32_t i = lenght(str) - 1; i >= 0; i--)
    {
        result += (str[i] - '0') * k;
        k = k * 10;
    }
    return result;
}
