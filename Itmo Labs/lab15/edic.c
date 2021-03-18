#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_FILE_OPEN -3

struct file_header
{
    int name_size;
    int data_size;
};

int main(int argc, char *argv[])
{
    if (argc > 2)
    {

        char *arc_name = argv[2];

        if (argv[3][2] == 'c')
        {
            //printf(" V   --create\n");
            int files_amount = argc - 4;
            FILE *arc;
            if ((arc = fopen(arc_name, "wb")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }
            fwrite(&files_amount, sizeof(int), 1, arc);
            //printf(" files_amount: %d\n", files_amount);
            for (int i = 4; i < argc; i++)
            {
                FILE *f;
                if ((f = fopen(argv[i], "rb")) == NULL)
                {
                    printf("%s %s Unable to open file", argv[i]);
                    exit(1);
                }
                int file_data_size = 0;
                while (getc(f) != EOF)
                {
                    file_data_size++;
                }
                fclose(f);
                if ((f = fopen(argv[i], "rb")) == NULL)
                {
                    printf("%s %s Unable to open file", argv[i]);
                    exit(1);
                }
                struct file_header fh;
                fh.name_size = strlen(argv[i]);
                fh.data_size = file_data_size;
                //printf(" %s   %d   %d\n", argv[i], fh.name_size, fh.data_size);
                fwrite(&fh, sizeof(int), 1, arc);
                fwrite(argv[i], sizeof(char), fh.name_size, arc);

                fwrite(&fh.data_size, sizeof(int), 1, arc);

                char *buf;

                buf = (char *)malloc(fh.data_size * sizeof(char));

                fread(buf, 1, fh.data_size, f);

                fwrite(buf, 1, fh.data_size, arc);

                fclose(f);
            }
            fclose(arc);

            // перевод бинарного файла в текстовый
            if ((arc = fopen(arc_name, "rb")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }

            FILE *arc_txt;

            if ((arc_txt = fopen("data/arc.txt", "wt")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }

            int *buf_i;

            buf_i = (int *)malloc(sizeof(int));

            fread(buf_i, sizeof(int), 1, arc);

            int files_number = *buf_i;

            fprintf(arc_txt, "number of files: %d\n---\n", *buf_i);

            for (int q = 0; q < files_number; q++)
            {
                fread(buf_i, sizeof(int), 1, arc);

                int current_file_name_size = *buf_i;

                fprintf(arc_txt, "filename size: %d\nfilename: ", *buf_i);

                char *buf_c;

                buf_c = (char *)malloc(sizeof(char));

                for (int i = 0; i < current_file_name_size; i++)
                {
                    fread(buf_c, 1, 1, arc);
                    fprintf(arc_txt, "%c", *buf_c);
                }

                fprintf(arc_txt, "\n");

                fread(buf_i, sizeof(int), 1, arc);

                int current_file_data_size = *buf_i;

                fprintf(arc_txt, "file data size: %d\n", *buf_i);

                for (int i = 0; i < current_file_data_size; i++)
                {
                    fread(buf_c, 1, 1, arc);
                    fprintf(arc_txt, "%c", *buf_c);
                }
                fprintf(arc_txt, "\n---\n");
            }
            fclose(arc);
            fclose(arc_txt);
        }
        else if (argv[3][2] == 'e')
        {
            FILE *arc;
            //printf("%s\n", argv[2]);
            if ((arc = fopen(argv[2], "rb")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }
            int files_number;

            fread(&files_number, sizeof(int), 1, arc);
            printf("%d\n", files_number);
            for (int i = 0; i < files_number; i++)
            {
                int file_data_size;

                int filename_size;

                //fread(&filename_size, sizeof(int), 1, arc);
                filename_size = 16;
                printf("%d\n", filename_size);

                char *filename;
                filename = (char *)malloc(filename_size);

                fread(filename, filename_size, 1, arc);

                printf("--%s\n", filename);
                printf("--%d\n", strlen(filename));
                //printf("\n");
                /*
                for (int j = 0; j < filename_size; j++) {
                    printf("%c", filename[j]);
                }
                printf("\n");
                */

                FILE *f;

                char fn[filename_size];

                //printf("%d\n", filename_size);
                for (int j = 0; j < filename_size; j++)
                {
                    fn[j] = filename[j];
                }
                //printf("\n");

                //printf("%s\n", filename);
                printf("%s\n", fn);

                if ((f = fopen(fn, "wb")) == NULL)
                {
                    printf("Cannot open file.\n");
                    exit(1);
                }

                fread(&file_data_size, sizeof(int), 1, arc);

                char *buf;

                buf = (char *)malloc(file_data_size * sizeof(char));

                fread(buf, sizeof(char) * file_data_size, 1, arc);

                fwrite(buf, file_data_size * sizeof(char), 1, f);

                fclose(f);
            }
            fclose(arc);
        }
        else if (argv[3][2] == 'l')
        {
            FILE *arc;
            if ((arc = fopen(argv[2], "rb")) == NULL)
            {
                printf("Cannot open file.\n");
                exit(1);
            }
            int files_number;
            int filename_size;
            int file_data_size;
            fread(&files_number, sizeof(int), 1, arc);
            for (int i = 0; i < files_number; i++)
            {
                fread(&filename_size, sizeof(int), 1, arc);

                char *filename;
                filename = (char *)malloc(filename_size * sizeof(char));

                fread(filename, sizeof(char), filename_size, arc);

                for (int j = 0; j < filename_size; j++)
                {
                    printf("%c", filename[j]);
                }
                printf("\n");

                fread(&file_data_size, sizeof(int), 1, arc);

                char *buf;

                buf = (char *)malloc(file_data_size * sizeof(char));

                fread(buf, sizeof(char), file_data_size, arc);
            }
            fclose(arc);
        }
    }

    return 0;
}
