
/**
 * This program reads a text file and prints the contents to the screen.
 *
 * @author Nirre Pluf {@literal <pluf@wfu.edu>}
 * @date Jan. 28, 2021
 * @assignment Lab 0
 * @course CSC 250
 **/

#include <stdio.h>
#define CHUNK 1024 /* read 1024 bytes at a time */

int main(int argc, char* argv[])
{
    char buffer[CHUNK]; /* buffer for data read from file */
    FILE* file_ptr;     /* file pointer */
    size_t nread;       /* number of bytes read from file */

    /* make certain we have enough command line arguments */
    if(argc < 2) {
        printf("Usage: %s file_name \n", argv[0]);
        return 1;
    }

    /* try to open the file and read */
    file_ptr = fopen(argv[1], "re");
    if(file_ptr) {
        /* read upto CHUNK bytes and print to the screen */
        while((nread = fread(buffer, 1, sizeof(buffer), file_ptr)) > 0)
            printf("%s ", buffer);
        fclose(file_ptr);
    }
    else {
        printf("%s cannot open %s \n", argv[0], argv[1]);
        return 1;
    }

    return 0;
}
