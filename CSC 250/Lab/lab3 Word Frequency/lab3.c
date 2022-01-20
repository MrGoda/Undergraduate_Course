/**
 * @author Patrick Fan {@literal }
 * @date March 8th, 2021
 * @assignment Lab 3
 * @course CSC 250
 **/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CSTRING_LENGTH 20



/* struct declaration */
struct WordFreq {
    char *word; /* the word */
    int count; /* the word frequency */
};


/* function declaration */
int process_words (char filename[], struct WordFreq **ptr_wdlist, int *num_words);
void print_words (char filename[], struct WordFreq **ptr_wdlist, int const *num_words);
void store (struct WordFreq **ptr_wdlist, int *num_words, char *cl, int cl_log_size);
int compare (char const *arr1, int cl_log_size, char const *arr2);


int main (int argc, char *argv[]) {
    int i = 0;
    struct WordFreq *word_list = NULL; /* list storing all the words */
    int num_words = 0; /* the logical length of word_list */

    struct WordFreq **ptr_wdlist = &word_list; /* pointer to the word list */
    int *ptr_num_words = &num_words; /* pointer that will pass this logical size to functions */

    int fileOK = 1;		/* status of the input file */

    /* Test if the input syntax is correct */
    if (argc < 3) {
        printf ("Usage: %s input_filename output_filename \n", argv[0]);	/*output the correct syntax */
        return 1;
    }

    /* process the input file and test if the file is processable */
    fileOK = process_words (argv[1], ptr_wdlist, ptr_num_words);

    /* if the file is not processable (return value is not 0) */
    if (!fileOK) {
        printf ("%s could not open file %s \n", argv[0], argv[1]);
        return 2;
    }

    /* print characters if file is okay */
    print_words (argv[2], ptr_wdlist, ptr_num_words);

    /* free memory allocated to word_list */
    for (i = 0; i < num_words; i ++) {
        free (word_list[i].word);
    }
    
    free (word_list);

    return 0;
}


/**
 *  Function to process words in the input file.
 *  If the input file is processable, store the words and their corresponding frequency in the word_list array.
 *  Return 1 if the file is processable, return 0 if filename points to nothing
 */
int process_words (char filename[], struct WordFreq **ptr_wdlist, int *num_words) {
    /* variables */
    int i;
    char ch; /* temporarily stores characters from the input file */
    char cl[MAX_CSTRING_LENGTH]; /* temporarily stores the current word ready to be processed */
    int cl_log_size = 0; /* logical size of cl */
    FILE *filePtr = fopen (filename, "rie"); /* pointer to the input file */
  

    /* initialization */
    for (i = 0; i < MAX_CSTRING_LENGTH; i++) {
        cl[i] = '\0';
    }

    /* return false if the pointer points to nothing */
    if (filePtr == 0) {
        return 0;
    }

    /* characters processing */
    ch = fgetc (filePtr);
    while (ch != EOF) {
        int intCh = (int) ch;	/* char converted to int */

        if ((65 <= intCh && 90 >= intCh) || (97 <= intCh && 122 >= intCh)) {    /* Process all letters */
	        if (65 <= intCh && 90 >= intCh) {
	            intCh += 32;
	        }

	        if (cl_log_size < 19) { /* not reaching the end of cstring */
	            cl[cl_log_size] = (char) intCh;   /*add the character to the end of cl */
	            cl_log_size += 1;
	        }
	        else if (cl_log_size == 19) {   /* if the end of cstring is reached, process the word */

	            store (ptr_wdlist, num_words, cl, cl_log_size);
        
                /* re-initialize cl */
                for (i = 0; i < MAX_CSTRING_LENGTH; i++) {
	                cl[i] = '\0';
	            }
	            cl_log_size = 0;
	        }
	    }
    
        else {  /* process all non-letter */
	        if (cl_log_size > 0) {  /* process the stored word */
	           
	           store (ptr_wdlist, num_words, cl, cl_log_size);
        
                /* re-initialize cl */
                for (i = 0; i < MAX_CSTRING_LENGTH; i++) {
	                cl[i] = '\0';
	            }
	            cl_log_size = 0;
	        }
	    }
        ch = fgetc (filePtr); /* get next character */
    }
    fclose (filePtr);

    return 1;
}


/**
 *  Function to print the words found in the input file and output each word together with its frequency to the output file
 */
void print_words (char filename[], struct WordFreq **ptr_wdlist, int const *num_words) {
    /* initialization */
    int i;
    int j;
    int max = 0; /* store the max count */
    int max_pos = 0; /* store the position of the word with max frequency */
    FILE *filePtr = fopen (filename, "we");	/* pointer to the output file */

    printf ("There are %d words found in the file.", *num_words); /* print the number of words to screen */

    for (i = 0; i < *num_words; i++) { 

        for (j = 0; j < *num_words; j ++) { /* find max and the position of max */
            if ((*ptr_wdlist)[j].count > max) {
                max = (*ptr_wdlist)[j].count;
                max_pos = j;
            }
	    }
	        
	    /* output this line to the output file */
        fputs ((*ptr_wdlist)[max_pos].word, filePtr);
        fputs (" ", filePtr);
        fprintf (filePtr, "%d", (*ptr_wdlist)[max_pos].count);
        fputs ("\n", filePtr);

        /* prevent the max_pos to be counted in the next loop */
        (*ptr_wdlist)[max_pos].count = 0;
	        
        max = 0;
        max_pos = 0;
    }
    fclose (filePtr);
}


/**
 *  Function to store the characters in the cstring to the struct word_list 
 */

void store (struct WordFreq **ptr_wdlist, int *num_words, char *cl, int cl_log_size) {
    /* variables list */
    int i;
    int j;
    int pos = 0; /* keep track of some position we want to store */
    int found = 0;  /* variable denoting whether a word is found */
    struct WordFreq *wdlist_temp = NULL;
    
    if (*num_words == 0) {  /* no element in the struct array */
        *ptr_wdlist = (struct WordFreq *) malloc (1 * sizeof (struct WordFreq));    /* dynamically allocate the wordlist */
        (*ptr_wdlist)[0].word = (char *) malloc ((cl_log_size + 1) * sizeof (char));	/* dynamically allocate the char array for the wordlist */
        
        for (i = 0; i <= cl_log_size; i++) {    /* copy cl to wdlist[0].word, including the NULL terminator */
	        (*ptr_wdlist)[0].word[i] = cl[i];
	    }
        
        (*ptr_wdlist)[0].count = 1;
        *num_words += 1;
    }
    
    else {  /* there already are elements in the struct array */
        found = 0;
        for (i = 0; i < *num_words && found == 0; i++) {  /* for each word stored in word list */

            /* find the length of (*ptr_wdlist)[i].word by checking the null terminator */
	        for (j = 0; pos == 0 && j < MAX_CSTRING_LENGTH; j++) {  
	            if ((*ptr_wdlist)[i].word[j] == '\0') {
		            pos = j;
		        }
	        }
        
            if (cl_log_size == pos) {
                if (compare (cl, cl_log_size, (*ptr_wdlist)[i].word)) { /* if cl is found in the wdlist, add one to count */
                    (*ptr_wdlist)[i].count += 1;
	                found = 1; /* report found to avoid later steps */
                }
            }
            pos = 0; /* make pos 0 again */
        }

        if (found == 0) {   /* if the word is not found */
	        
	        /* dynamically allocate a new wordlist with original size + 1 */
	        wdlist_temp = (struct WordFreq *) malloc ((*num_words + 1) * sizeof (struct WordFreq));	
	        
	        for (i = 0; i < *num_words; i++) {  /* loop through the orginal wordlist and copy all elements to the new one */

	            for (j = 0; j < MAX_CSTRING_LENGTH && pos == 0; j ++) {  /* find the length of (*ptr_wdlist)[i].word by checking the null terminator */
		            if ((*ptr_wdlist)[i].word[j] == '\0') {
		                pos = j;
		            }
		        }
	            wdlist_temp[i].word = (char *) malloc ((pos + 1) * sizeof (char));
	            
	            for (j = 0; j <= pos; j++) {
		            wdlist_temp[i].word[j] = (*ptr_wdlist)[i].word[j];	/* copy word, including the NULL terminator */
		        }
	            wdlist_temp[i].count = (*ptr_wdlist)[i].count;	/* copy counts */

	            pos = 0; /* make pos 0 again */
                
	        }

	        wdlist_temp[*num_words].word = (char *) malloc ((cl_log_size + 1) * sizeof (char));	/* new word */
	        for (i = 0; i <= cl_log_size; i++) { /* copy word stored in cl */
	            wdlist_temp[*num_words].word[i] = cl[i];
	        }
	        wdlist_temp[*num_words].count = 1;
            *num_words += 1;
            
            for (i = 0; i < *num_words - 1; i ++) {
                free ((*ptr_wdlist)[i].word);	/* free memory for dynamically allocated word */
            }
	        free (*ptr_wdlist);	/* free memory of the orginal wdlist */

	        *ptr_wdlist = (struct WordFreq *) malloc ((*num_words) * sizeof (struct WordFreq));	/* allocate new memory space */

	        for (i = 0; i < *num_words; i++) {  /* loop through the temporary wordlist */
	            for (j = 0; j < MAX_CSTRING_LENGTH && pos == 0; j++) {  /* find the length of (*ptr_wdlist)[i].word */
		            if (wdlist_temp[i].word[j] == '\0') {
                        pos = j;
                    }
	            }
	            
	            (*ptr_wdlist)[i].word = (char *) malloc ((pos + 1) * sizeof (char));
	            
	            for (j = 0; j <= pos; j++) {
		            (*ptr_wdlist)[i].word[j] = wdlist_temp[i].word[j];	/* copy word */
		        }
	            (*ptr_wdlist)[i].count = wdlist_temp[i].count;	/* copy counts */
	            
	            pos = 0;
		    }
		    for (i = 0; i < *num_words; i ++) {
		        free (wdlist_temp[i].word);	/* free memory for dynamically allocated word */
		    }
		    
		    free (wdlist_temp);	/*free memory of the temporary wdlist */
		}
    }
}




/**
 *  Function to compare two arrays. cl_log_size refers to the logical size of the first array. 
 *  Return 1 if they are the same and 0 if not. 
 */
int compare (char const *arr1, int cl_log_size, char const *arr2) {
    int i;

    for (i = 0; i < cl_log_size; i ++) {
	    if (arr1[i] != arr2[i]) {
	        return 0;
	    }
	}
    return 1;
}