#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Кол-во файлов
//Перечисление файлов: кол-во байт на название_название_кол-во байт на содержимое_содержимое

void createArchive(char *filename, int N, char **toArchive)
{
    int size_name, size_file;
    char c;
    FILE *output = fopen(filename, "wb");
    fwrite(&N, sizeof(int), 1, output);
    for (int i = 0; i < N; i++)
    {
        FILE *writeFile = fopen(toArchive[i], "rb");
        if (writeFile == NULL)
        {
            printf("File: %s doen't exist, skip \n", toArchive[i]);
            continue;
        }
        size_name = strlen(toArchive[i]);
        fseek(writeFile, 0, SEEK_END);
        size_file = ftell(writeFile);
        fseek(writeFile, 0, 0);

        if (size_file == -1L)
        {
            printf("File: %s is empty\n", toArchive[i]);
            continue; //
        }

        fwrite(&size_name, sizeof(int), 1, output);
        fwrite(toArchive[i], size_name, 1, output);
        fwrite(&size_file, sizeof(int), 1, output);

        for (int j = 0; j < size_file; j++)
        {
            c = getc(writeFile);
            putc(c, output);
        }
        fclose(writeFile);
        printf("File: %s Done\n", toArchive[i]);
    }
    fclose(output);
}

void readArchive(char *filename)
{
    FILE *Archive = fopen(filename, "rb");
    int N, size_name, size_file;
    char *name;
    fread(&N, sizeof(int), 1, Archive);
    printf("File amount %d\n", N);
    for (int i = 0; i < N; i++)
    {
        fread(&size_name, sizeof(int), 1, Archive);
        name = (char*) malloc(size_name * sizeof(char));
        fread(name, sizeof(char) * size_name, 1, Archive);
        printf("%s\n", name);
        free(name);
        fread(&size_file, sizeof(int), 1, Archive);
        fseek(Archive, size_file, SEEK_CUR);
    }
}

void createFromArchive(char *filename)
{
    FILE *Archive = fopen(filename, "rb");
    int N, size_name, size_file;
    char *name, c;
    fread(&N, sizeof(int), 1, Archive);
    for (int i = 0; i < N; i++)
    {
        fread(&size_name, sizeof(int), 1, Archive);
        name = (char*) malloc(size_name * sizeof(char));
        fread(name, sizeof(char) * size_name, 1, Archive);
        fread(&size_file, sizeof(int), 1, Archive);

        FILE *output = fopen(name, "wb");
        for (int i = 0; i < size_file; i++)
        {
            c = getc(Archive);
            putc(c, output);
        }

        printf("File: %s extracted\n", name);
        free(name);
        fclose(output);
    }
}
//
int main(int argc, char *argv[])
{
    char filename[100];
    char *files[50];
    int k = 0, m;
    for(int i = 0; i < argc; i++)
    {
        if (argv[i][2] == 'f' && argv[i][3] == 'i' && argv[i][4] == 'l')
        {
            strncpy(filename, argv[i + 1], 100);
        }
            
        if (argv[i][2] == 'e' && argv[i][3] == 'x' && argv[i][4] == 't')
            createFromArchive(filename);
        if (argv[i][2] == 'l' && argv[i][3] == 'i' && argv[i][4] == 's')
            readArchive(filename);
            
        if (argv[i][2] == 'c' && argv[i][3] == 'r' && argv[i][4] == 'e')
        {
            
            while (i < argc - 1)
            {
                i++;
                /*for (int p = 0; argv[i][p] != '\0'; p++)
                {
                    files[k][p] = argv[i][p];
                    m = p;
                }
                files[k][m + 1] = '\0';*/
                files[k] = malloc(strlen(argv[i]) * sizeof(char));
                strncpy(files[k], argv[i], 100);
                k++;
            }
            createArchive(filename, k, files);

        }
    }
    
    
}