// !test bad_file_access
#include<iostream> // without
#include <cstdio>

int main ()
{
    char *filename = "file.txt";
    int acc = access(filename, 0);
    if (aсс == 0)
    {
        FILE * ptrFile = fopen(filename, "w");

        if (ptrFile != NULL)
        {
            fputs("Nice! ", ptrFile);
            fclose (ptrFile);
        }
    }
return 0;
}