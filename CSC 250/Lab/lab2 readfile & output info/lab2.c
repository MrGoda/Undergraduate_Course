/**
 * This program reads a text file and prints the top 5 most frequent letters (upper or lower case)
 * and the top 5 most frequent digits that are in the file. If the file has less than 5 unique letters
 * and/or digits the top list is adjusted accordingly. The file name is provided using command line 
 * arguments. If the file name is not provided or the file is not readable, the program will exit
 * and provide an error message.
 *
 * @author Patrick Fan Here {@literal }
 * @date Feb.23, 2021
 * @assignment Lab 2
 * @course CSC 250
 **/


#include <stdio.h>
#define MAX_STRING_SIZE 20
#define MAX_LIST_SIZE 36


/* a useful struct, if you choose to use it  */  
struct Char_Freq {
    char ch;
    int count;
};

/* Array of struct to be used */
struct Char_Freq cf[10];


/* function declarations go here */
int process_characters(char filename[], int *arr);
void print_characters(int *arr);


int main(int argc, char* argv[]){
    /* Initialization */
    int fileOK = 1;
    int arr[MAX_LIST_SIZE];  
    int i;

    for (i = 0; i < MAX_LIST_SIZE; i ++){
        arr[i] = 0;
    }


    /* if the input structure is incorrect */
    if(argc < 2){
        printf("Usage: %s filename \n", argv[0]);
        return 1;
    }

    /* process the file and test if the file is processable. */
    fileOK = process_characters(argv[1], arr);
    if(!fileOK){
        printf("%s could not open file %s \n", argv[0], argv[1]);
        return 2;
    }

/* print characters if file is okay */
print_characters(arr);

    return 0;
}

/**
* Function to process characters from a file$
* Input a filename and an array, process every character in the file,$
* and count the frequency of each character or digit in the array.$
* Return an integer representing if the file is successfully processed.$
**/
int process_characters(char filename[], int *arr){\
    /* Initialization */
    char ch;  /* char type used to temporarily store each of the character */ 
    FILE *filePtr = fopen(filename, "rie"); /* pointer to the file content */

    /* return false if the pointer points to nothing */
    if(filePtr == 0)
        return 0;

    /* output each character to ch */
    ch = fgetc(filePtr);
    while(ch != EOF){ /* while ch is not empty */
        int intCh = (int) ch; /* char converted to int */
        if (65 <= intCh && 90 >= intCh){ /* A~Z */
            intCh += 32;
            arr[intCh-97] += 1;
        }
        else if (97 <= intCh && 122 >= intCh){ /* a~z */
            arr[intCh-97] += 1;
        }
        else if (48 <= intCh && 57 >= intCh){ /* 0~9 */
            arr[intCh-22] += 1;
        }
        ch = fgetc(filePtr); /* store the next character */
    }

    fclose(filePtr); /* close the file */

    return 1;
}


/**
* Function to print the frequency of characters and digits.$
* Input an array storing the frequency of characters and digits.$
* Output the top 5 letters and top 5 numbers used in the file.$
**/
void print_characters(int *arr){
int i;
int j;
int k;
int l;
int m;
int n;
for (i = 0; i < 5; i ++){ /* loop through top 5 frequency */
    /* Initialization */
    cf[i].ch = '\0';
    cf[i].count = 0; 
    for (j = 0; j < 26; j ++){ /* loop through 26 characters */
        if (arr[j] > cf[i].count){ 
            cf[i].count = arr[j]; 
            cf[i].ch = (char) (j + 97);
        }
    }
    
	arr[((int) cf[i].ch)-97] = 0; /* avoid this frequency in next loop */
    }

for (k = 5; k < 10; k ++){ /* loop through top 5 frequency */
    cf[k].count = 0;
    for (l = 26; l < 36; l ++){ /* loop through 10 digits */
        if (arr[l] > cf[k].count){
            cf[k].count = arr[l];
            cf[k].ch = (char) (l + 22);
        }
    }
    
	arr[((int) cf[k].ch)-22] = 0; /* avoid this frequency in next loop */
}

for (m = 0; m < 5; m ++){ /* loop through top 5 frequency */
    if (cf[m].ch != '\0'){ /* if the character is not empty */
        printf("%c: %d \n", cf[m].ch, cf[m].count);
    }
    else{
        if (m == 0){ /* if there are no characters at all*/
            printf("No letters found. \n");
        }
    }
}

for (n = 5; n < 10; n ++){
    if (cf[n].ch != '\0'){ /* if the digit is not empty */
        printf("%c: %d \n", cf[n].ch, cf[n].count);
    }
    else{
        if (n == 5){
            printf("No digits found. \n"); /* if there are no digits at all*/
        }
    }
}
}

