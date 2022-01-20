#include "get_wav_args.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* function declarations */
int read_wav_header(FILE *wav_file, FILE *new_wav_file, short *num_channels_ptr, short *sample_size_ptr, int *num_sample_ptr);
void read_wav_data(FILE *wav_file, FILE *new_wav_file, FILE *text_file, int num_bits, short sample_size);

int main(int argc, char *argv[]) {
    /* variable declarations */
    FILE *wav_file;
    FILE *new_wav_file;
    FILE *text_file;
    short sample_size; /* the length of one sample */
    short num_channels; /* number of channels */
    int num_samples; /* numbers of samples */
    int wav_ok = 0; /* if the wav file is okay for processing */
    int bit;
    char wav_file_name[256];
    char text_file_name[256];
    char new_wav_file_name[256];
    int args_ok;
    
    args_ok = get_wav_args(argc, argv, &bit, wav_file_name, text_file_name); /* determines if the input style is correct */
    if (!args_ok) {
        return 1;
    }
    
    /* test if the wav file we want to process ends with ".wav" */
    if (strcmp(wav_file_name + strlen(wav_file_name) - 4, ".wav") != 0) {
        printf("wav file %s missing \".wav\" \n", wav_file_name);
        return 0;
    }
    strcpy(new_wav_file_name, wav_file_name);
    strcpy((new_wav_file_name + strlen(new_wav_file_name) - 4), "_msg.wav");
    
    /* open the wav file with original data */
    wav_file = fopen(wav_file_name, "rbe"); /* opens the input file */
    if (!wav_file) {
        printf("Could not open wav file %s \n", wav_file_name);
        return 2;
    }
    
    text_file = fopen(text_file_name, "re");
    if (!text_file) {
        printf("Could not open wav file %s \n", text_file_name);
        return 2;
    }
    
    /* open the wav file to store text */
    new_wav_file = fopen(new_wav_file_name, "wbe"); /* opens the output file */
    if (!new_wav_file) {
        printf("Could not create wav file %s \n", new_wav_file_name);
        return 2;
    }
    
    wav_ok = read_wav_header(wav_file, new_wav_file, &num_channels, &sample_size, &num_samples);
    
    if (wav_ok != 1) { /* the audio format is incorrect */
        printf("Audio format not PCA, processing terminated.");
        return 3;
    }
    

    read_wav_data(wav_file, new_wav_file, text_file, bit, sample_size);

    printf("%s \n", new_wav_file_name);

    fclose(wav_file);
    fclose(new_wav_file);
    fclose(text_file);
    return 0;
}

/**
 * function to read the headers of samples until reading the header of "data". 
 * the function stores information given from the wav file, output information to screen,
 * and return 1 if the audio_format is in PCA form (return 0 if not).
 **/
int read_wav_header(FILE *wav_file, FILE *new_wav_file, short *num_channels_ptr, short *sample_size_ptr, int *num_sample_ptr) {
    /* variables declarations */
    char chunk_id[] = "    ";
    char data[] = "    ";
    int chunk_size = 0;
    short audio_format = 0;
    int sample_rate = 0;
    int byte_rate = 0;
    short block_assigned_rate = 0;
    
    /* read and write the RIFF chunk */
    fread(chunk_id, 4, 1, wav_file);
    fwrite(chunk_id, 4, 1, new_wav_file);
    fread(&chunk_size, 4, 1, wav_file);
    fwrite(&chunk_size, 4, 1, new_wav_file);
    fread(data, 4, 1, wav_file);
    fwrite(data, 4, 1, new_wav_file);
    
    /* skip all chunks that is not "fmt ", write only the "fmt " chunk */
    fread(chunk_id, 4, 1, wav_file);
    while(strcmp(chunk_id, "fmt ") != 0) {
        fread(&chunk_size, 4, 1, wav_file);
        /* skip to the end of the chunk */
        fseek(wav_file, chunk_size, SEEK_CUR);
        /* read id of the next chunk */
        fread(chunk_id, 4, 1, wav_file);
    }
    fwrite(chunk_id, 4, 1, new_wav_file);
    
    /* now we have the fmt chunk, read and write information in this chunk */
    fread(&chunk_size, 4, 1, wav_file);
    fwrite(&chunk_size, 4, 1, new_wav_file);
    
    fread(&audio_format, 2, 1, wav_file);
    fwrite(&audio_format, 2, 1, new_wav_file);
    
    fread(num_channels_ptr, 2, 1, wav_file);
    fwrite(num_channels_ptr, 2, 1, new_wav_file);
    
    fread(&sample_rate, 4, 1, wav_file);
    fwrite(&sample_rate, 4, 1, new_wav_file);
    
    fread(&byte_rate, 4, 1, wav_file);
    fwrite(&byte_rate, 4, 1, new_wav_file);
    
    fread(&block_assigned_rate, 2, 1, wav_file);
    fwrite(&block_assigned_rate, 2, 1, new_wav_file);
    
    fread(sample_size_ptr, 2, 1, wav_file); /* bits per sample */
    fwrite(sample_size_ptr, 2, 1, new_wav_file); 
    
    /* read the data chunk next, use another while loop to skip other chunks */
    fread(chunk_id, 4, 1, wav_file);
    while(strcmp(chunk_id, "data") != 0) {
        fread(&chunk_size, 4, 1, wav_file);
        /* skip to the end of the chunk */
        fseek(wav_file, chunk_size, SEEK_CUR);
        /* read id of the next chunk */
        fread(chunk_id, 4, 1, wav_file);
    }
    fwrite(chunk_id, 4, 1, new_wav_file);
    
    /* here chunk_id should have "data" stored */
    fread(&chunk_size, 4, 1, wav_file);
    fwrite(&chunk_size, 4, 1, new_wav_file);
    
    /* calculate num_samples and duration here */
    *num_sample_ptr = (chunk_size * 8) / (*sample_size_ptr);
    if (*num_channels_ptr == 2) {
        *num_sample_ptr = *num_sample_ptr / 2;
    }
    
    return (audio_format == 1);
}

/**
 * function to read the actual data until all samples are read.
 * write sample data, with text hidden, into the new_wav_file.
 **/
void read_wav_data(FILE *wav_file, FILE *new_wav_file, FILE *text_file, int num_bits, short sample_size) {
    /* variable declarations */
    int i;
    char ch;
    unsigned char ch_temp = '\0';
    int ch_count = 0; /* count the number of characters stored */
    int sample;
    unsigned int mask;
    unsigned int maskB;
    
    /* initialization */
    sample = 0;
    
    /* create appropriate mask */
    if (num_bits == 1) {
        if (sample_size == 8) {
            mask = 254;
        }
        else {
            mask = 65534;
        }
        
        maskB = 1;
    }
    else if (num_bits == 2) {
        if (sample_size == 8) {
            mask = 252;
        }
        else {
            mask = 65532;
        }
        maskB = 3;
    }
    else {
        if (sample_size == 8) {
            mask = 240;
        }
        else {
            mask = 65520;
        }
        maskB = 15;
    }
    
    /* get content from text_file */
    ch = fgetc(text_file);
    
    while (ch != EOF) {
        for (i = 0; i < (8 / num_bits); i ++) {
            
            /* convert sample into appropriate type */
            fread(&sample, (sample_size / 8), 1, wav_file);
            if ((sample_size / 8) == 2) {
                sample = (short) sample;
            }
            
            ch_temp = ch;
            sample = ((unsigned int)sample & mask) | ((unsigned int) (ch_temp >> (unsigned int) (8 - (i + 1) * num_bits)) & maskB);
            
            /* write into new_wav_file */
            fwrite(&sample, (sample_size / 8), 1, new_wav_file);
        }
        
        ch_count += 1;
        ch = fgetc(text_file);
    }
    
    /* write :) into new_wav_file */
    ch = ':';
    for (i = 0; i < (8 / num_bits); i ++) {
            
        /* convert sample into appropriate type */
        fread(&sample, (sample_size / 8), 1, wav_file);
        if ((sample_size / 8) == 2) {
            sample = (short) sample;
        }
            
        ch_temp = ch;
        sample = ((unsigned int)sample & mask) | ((unsigned int) (ch_temp >> (unsigned int) (8 - (i + 1) * num_bits)) & maskB);
            
        /* write into new_wav_file */
        fwrite(&sample, (sample_size / 8), 1, new_wav_file);
    }
    ch_count += 1;
    
    ch = ')';
    for (i = 0; i < (8 / num_bits); i ++) {
            
        /* convert sample into appropriate type */
        fread(&sample, (sample_size / 8), 1, wav_file);
        if ((sample_size / 8) == 2) {
            sample = (short) sample;
        }
            
        ch_temp = ch;
        sample = ((unsigned int)sample & mask) | ((unsigned int) (ch_temp >> (unsigned int) (8 - (i + 1) * num_bits)) & maskB);
            
        /* write into new_wav_file */
        fwrite(&sample, (sample_size / 8), 1, new_wav_file);
    }
    ch_count += 1;
    
    ch = EOF;
    for (i = 0; i < (8 / num_bits); i ++) {
            
        /* convert sample into appropriate type */
        fread(&sample, (sample_size / 8), 1, wav_file);
        if ((sample_size / 8) == 2) {
            sample = (short) sample;
        }
            
        ch_temp = ch;
        sample = ((unsigned int)sample & mask) | ((unsigned int) (ch_temp >> (unsigned int) (8 - (i + 1) * num_bits)) & maskB);
            
        /* write into new_wav_file */
        fwrite(&sample, (sample_size / 8), 1, new_wav_file);
    }
    ch_count += 1;
    
    /* print summary info */
    printf("%d characters written to ", ch_count);
    
}