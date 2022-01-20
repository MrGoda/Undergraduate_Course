/**
 * This program reads a WAV audio file and prints statistics about the audio samples. The file name 
 * is provided using command line arguments. If the file name is not provided or the file is not readable, 
 * the program will exit and provide an error message.
 *
 * @author Patrick Fan Here {@literal <pluf@wfu.edu>}
 * @date Mar. 7, 2021
 * @assignment Lab 4  
 * @course CSC 250
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function declarations */
int read_wav_header(FILE *in_file, short *num_channels_ptr, short *sample_size_ptr, int *num_sample_ptr, int *sample_rate_ptr);
void read_wav_data(FILE *in_file, short num_channels, short sample_size, int num_samples);

int main(int argc, char *argv[]) {
    /* variable declarations */
    FILE *in_file;
    short sample_size; /* the length of one sample */
    short num_channels; /* number of channels */
    int sample_rate; /* bits per second */
    int num_samples; /* numbers of samples */
    int wav_ok = 0; /* if the wav file is okay for processing */
    
    if (argc < 2) { /* incorrect input style */
        printf("usage: %s wave_file \n", argv[0]);
        return 1;
    }
    
    in_file = fopen(argv[1], "rbe"); 
    
    
    if(!in_file) { /* if the file cannot be opened */ 
        printf("could not open wav file %s \n", argv[1]);
        return 2;
    }
    
    wav_ok = read_wav_header(in_file, &num_channels, &sample_size, &num_samples, &sample_rate);
    
    if (wav_ok != 1) { /* the audio format is incorrect */
        printf("Audio format not PCA, processing terminated.");
        return 2;
    }
    
    read_wav_data(in_file, num_channels, sample_size, num_samples);

    fclose(in_file);
    return 0;
}

/**
 * function to read the headers of samples until reading the header of "data". 
 * the function stores information given from the wav file, output information to screen,
 * and return 1 if the audio_format is in PCA form (return 0 if not).
 **/
int read_wav_header(FILE *in_file, short *num_channels_ptr, short *sample_size_ptr, int *num_sample_ptr, int *sample_rate_ptr) {
    /* variables declarations */
    char chunk_id[] = "    ";
    char data[] = "    ";
    int chunk_size = 0;
    short audio_format = 0;
    int byte_rate = 0;
    short block_assigned_rate = 0;
    
    /* read the RIFF chunk */
    fread(chunk_id, 4, 1, in_file);
    fread(&chunk_size, 4, 1, in_file);
    printf("chunk: %s, size: %d \n", chunk_id, chunk_size);
    fread(data, 4, 1, in_file);
    printf("  data: %s \n", data);
    
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
    fread(sample_rate_ptr, 4, 1, in_file);
    fread(&byte_rate, 4, 1, in_file);
    fread(&block_assigned_rate, 2, 1, in_file);
    fread(sample_size_ptr, 2, 1, in_file); /* bits per sample */
    
    /* output information stored */
    printf("chunk: %s, size: %d \n", chunk_id, chunk_size);
    printf("  audio_format: %d \n", audio_format);
    printf("  num channels: %d \n", *num_channels_ptr);
    printf("  sample rate: %d \n", *sample_rate_ptr);
    printf("  bits per sample: %d \n", *sample_size_ptr);
    
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
    printf("chunk: %s, size: %d \n", chunk_id, chunk_size);
    
    /* calculate num_samples and duration here */
    *num_sample_ptr = (chunk_size * 8) / (*sample_size_ptr);
    if (*num_channels_ptr == 2) {
        *num_sample_ptr = *num_sample_ptr / 2;
    }
    printf("  num samples: %d \n", *num_sample_ptr);
    printf("  duration: %f \n", ((double) (*num_sample_ptr) / (double) (*sample_rate_ptr)));
    
    return (audio_format == 1);
}

/**
 * function to read the actual data until all samples are read.
 * the function determines the largest sample in absolute value and output it to the screen.
 **/
void read_wav_data(FILE *in_file, short num_channels, short sample_size, int num_samples) {
    /* variable declarations */
    int i;
    int sample;
    int max[2]; /* max[0] is for mono or left sample, max[1] is for right sample */
    
    /* initialization */
    sample = 0;
    max[0] = 0;
    max[1] = 0;
    
    if (num_channels == 1) { /* if there is only one channel */
        for (i = 0; i < num_samples; i ++) {
            /* convert sample into appropriate type */
            fread(&sample, (sample_size / 8), 1, in_file);
            if ((sample_size / 8) == 2) {
                sample = (short) sample;
            }
            
            /* store the larger of the sample into max */
            if (abs(sample) > max[0]) {
                max[0] = abs(sample);
            }
        }
        printf("  max abs mono sample: %d \n", max[0]);
    }
    else if (num_channels == 2) { /*if there are two samples */
        for (i = 0; i < num_samples; i ++) {
            /* first process the left sample; convert left sample into appropriate type */
            fread(&sample, (sample_size / 8), 1, in_file);
            if ((sample_size / 8) == 2) {
                sample = (short) sample;
            }
            
            /* store the larger of the sample into max */
            if (abs(sample) > max[0]) {
                max[0] = abs(sample);
            }
            
            /* then process the right sample */
            fread(&sample, (sample_size / 8), 1, in_file);
            if ((sample_size / 8) == 2) {
                sample = (short) sample;
            }
            
            /* store the larger of the sample into max */
            if (abs(sample) > max[1]) {
                max[1] = abs(sample);
            }
            
        }
        printf("  max abs left sample: %d \n", max[0]);
        printf("  max abs right sample: %d \n", max[1]);
    }
}