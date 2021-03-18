#include "bmp_things.h"
#include "bmp_things.c"
#include "rotate.h"
#include "rotate.c"
#include "utility.h"
#include "utility.c"
#include "IOFile.h"
#include "IOFile.c"

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    char filename[100];
    uint32_t angleDegree = 90;
    for (size_t i = 1; i < argc; i++)
    {
        if (argv[i][2] == 'f')
            strncpy(filename, argv[i + 1], 100);
        if (argv[i][2] == 'a')
            angleDegree = strToint(argv[i + 1]);
            
        if (argv[i][2] == 'h')
        {
            printf("INFO\n--file    - filename\n--angle   - set angle in degree. Default 90\n--help    - INFO\n");
            return 0;
        }
            
    }
    
    enum IOStatusO inpState = InputO(filename, &fin);
    if (inpState != 0)
    {
        printf("Open error %d\n", inpState);
        return -1;
    }
    printf("File: %s\n", filename);
    struct image img;

   
    enum read_status status = fromBmp(fin, &img);

    if (status == 0)
        printf("File has read sucsefull\n");
    else
    {
        printf("File can't read correctly\nError code: %d\n", status);
        fclose(fin);
        return -1;
    }
        
    img = rotate(img, angleDegree);

    inpState = OutputO("output.bmp", &fout);
    if (inpState != 0)
    {
        printf("Writing error %d", inpState);
        return -1;
    }

    enum write_status status2 = toBmp(fout, &img);
    if (status2 == 0)
        printf("New file has created sucsefull\n");
    else
    {
        printf("Can't create new file\nError code: %d", status);
        fclose(fin);
        fclose(fout);
        return -1;
    }

    if (InputC(&fin) != 0)
    {
        printf("Error while closing file\n");
        return -1;
    }
    if (OutputC(&fout) != 0)
    {
        printf("Error while closing file\n");
        return -1;
    }
    printf("DONE!");
    return 0;
}