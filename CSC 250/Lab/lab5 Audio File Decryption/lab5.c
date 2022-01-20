/**
 * This program reads a WAV audio file and finds the characters stored implicitly in the data. The file name 
 * is provided using command line arguments. If the file name is not provided or the file is not readable, 
 * the program will exit and provide an error message.
 *
 * @author Patrick Fan Here {@literal <pluf@wfu.edu>}
 * @date Mar. 29, 2021
 * @assignment Lab 5 
 * @course CSC 250
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_wav_args.h"

/* function declarations */
int read_wav_header(FILE *in_file, short *num_channels_ptr, short *sample_size_ptr, int *num_sample_ptr);
void read_wav_data(FILE *in_file, FILE *out_file, int num_bits, short num_channels, short sample_size, int num_samples);

int main(int argc, char *argv[]) {
    /* variable declarations */
    FILE *in_file;
    FILE *out_file;
    short sample_size; /* the length of one sample */
    short num_channels; /* number of channels */
    int num_samples; /* numbers of samples */
    int wav_ok = 0; /* if the wav file is okay for processing */
    int bit;
    char wav_file_name[256];
    char text_file_name[256];
    int args_ok;

    args_ok = get_wav_args(argc, argv, &bit, wav_file_name, text_file_name); /* determines if the input style is correct */
    if (!args_ok) {
        return 1;
    }
    
    in_file = fopen(argv[3], "rbe"); /* opens the input file */
    out_file = fopen(argv[4], "we"); /* opens the output file */
    
    
    if(!in_file) { /* if the file cannot be opened */ 
        printf("could not open wav file %s \n", argv[1]);
        return 2;
    }
    
    wav_ok = read_wav_header(in_file, &num_channels, &sample_size, &num_samples);
    
    if (wav_ok != 1) { /* the audio format is incorrect */
        printf("Audio format not PCA, processing terminated.");
        return 3;
    }
    
    read_wav_data(in_file, out_file, bit, num_channels, sample_size, num_samples);

    fclose(in_file);
    fclose(out_file);
    return 0;
}

/**
 * function to read the headers of samples until reading the header of "data". 
 * the function stores information given from the wav file
 * and return 1 if the audio_format is in PCA form (return 0 if not).
 **/
int read_wav_header(FILE *in_file, short *num_channels_ptr, short *sample_size_ptr, int *num_sample_ptr) {
    /* variables declarations */
    char chunk_id[] = "    ";
    char data[] = "    ";
    int chunk_size = 0;
    short audio_format = 0;
    int sample_rate = 0;
    int byte_rate = 0;
    short block_assigned_rate = 0;

    /* read the RIFF chunk */
    fread(chunk_id, 4, 1, in_file);
    fread(&chunk_size, 4, 1, in_file);
    fread(data, 4, 1, in_file);
    
    /* skip all chunks that is not "fmt " */
    fread(chunk_id, 4, 1, in_file);
    while(strcmp(chunk_id, "fmt ") != 0) {
        fread(&chunk_size, 4, 1, in_file);
        /* skip to the end of the chunk */
        fseek(in_file, chunk_size, SEEK_CUR);
        /* read id of the next chunk */
        fread(chunk_id, 4, 1, in_file);
    }
    
    /* now we have the fmt chunk, read information in this chunk */
    fread(&chunk_size, 4, 1, in_file);
    fread(&audio_format, 2, 1, in_file);
    fread(num_channels_ptr, 2, 1, in_file);
    fread(&sample_rate, 4, 1, in_file);
    fread(&byte_rate, 4, 1, in_file);
    fread(&block_assigned_rate, 2, 1, in_file);
    fread(sample_size_ptr, 2, 1, in_file); /* bits per sample */
    
    /* output information stored */
    
    /* read the data chunk next, use another while loop to skip other chunks */
    fread(chunk_id, 4, 1, in_file);
    while(strcmp(chunk_id, "data") != 0) {
        fread(&chunk_size, 4, 1, in_file);
        /* skip to the end of the chunk */
        fseek(in_file, chunk_size, SEEK_CUR);
        /* read id of the next chunk */
        fread(chunk_id, 4, 1, in_file);
    }
    
    /* here chunk_id should have "data" stored */
    fread(&chunk_size, 4, 1, in_file);
    
    /* calculate num_samples and duration here */
    *num_sample_ptr = (chunk_size * 8) / (*sample_size_ptr);
    if (*num_channels_ptr == 2) {
        *num_sample_ptr = *num_sample_ptr / 2;
    }
    
    return (audio_format == 1);
}

/**
 * function to read the actual data
 * and figrues out characters stored inplicitly in the data
 **/
void read_wav_data(FILE *in_file, FILE *out_file, int num_bits, short num_channels, short sample_size, int num_samples) {
    /* variable declarations */
    int i;
    int sample_count = 0; /* count the number of samples used */
    int ch_count = 0; /* count the number of characters */
    int smile_found = 0; /* whether or not ":)" is found */
    int sample;
    unsigned char ch = 0;
    unsigned char prev_ch = 0;
    unsigned int mask;
    
    /* initialization */
    sample = 0;
    
    /* create appropriate mask */
    if (num_bits == 1) {
        mask = 1;
    }
    else if (num_bits == 2) {
        mask = 3;
    }
    else {
        mask = 15;
    }
    
    if (num_channels == 1) { /* if there is only one channel */
        
        while ((sample_count < num_samples) && (smile_found != 1)) {
            
            /* read an 8 bits character */
            for (i = 0; i < (8 / num_bits); i ++) {
                /* convert sample into appropriate type */
                fread(&sample, (sample_size / 8), 1, in_file);
                if ((sample_size / 8) == 2) {
                    sample = (short) sample;
                }
                
                /* store bits into ch */
                ch = ch | (unsigned char) ((((unsigned int) sample) & mask) << ((unsigned int) (8 - ((i + 1) * num_bits))));
                sample_count += 1;

            }
            
            /* here we have a complete character, so write ch into out_file */
            fputc(ch, out_file);
            ch_count += 1;
            
            /* test if :) is detected */
            if ((prev_ch == ':') && (ch == ')')) {
                smile_found = 1;
            }
            
            /* set previous ch to the current one and set current ch to 0 */
            prev_ch = ch;
            ch = 0;
        }
    }
    
    else if (num_channels == 2) { /*if there are two samples */
    
        while ((sample_count < num_samples) && (smile_found != 1)) {
    
            /* read an 8 bits character */
            for (i = 0; i < (4 / num_bits); i ++) {
                /* convert sample into appropriate type */
                fread(&sample, (sample_size / 8), 1, in_file);
                if ((sample_size / 8) == 2) {
                    sample = (short) sample;
                }
                
                /* store bits into ch */
                ch = ch | (unsigned char) ((((unsigned int) sample) & mask) << ((unsigned int) (8 - ((i + 1) * num_bits))));

                fread(&sample, (sample_size / 8), 1, in_file);
                if ((sample_size / 8) == 2) {
                    sample = (short) sample;
                }
                
                /* store bits into ch */
                ch = ch | (unsigned char) ((((unsigned int) sample) & mask) << ((unsigned int) (8 - ((i + 1) * num_bits))));
                sample_count += 1; 

            }
    
            /* here we have a complete character, so write ch into out_file */
            fputc(ch, out_file);
            ch_count += 1;
    
            /* test if :) is detected */
            if ((prev_ch == ':') && (ch == ')')) {
                smile_found = 1;
            }
            
            /* set previous ch to the current one and set current ch to 0 */
            prev_ch = ch;
            ch = 0;
        }
    }
    
    printf("%d characters recovered from %d samples \n", ch_count, sample_count);
}