//
// Created by r2-ngimbimombo on 1/04/2026.
//
#include <stdio.h>      // Provides file input/output functions
#include <stdlib.h>     // Provides memory allocation functions
#include <string.h>     // Provides string manipulation functions
#include "waveform.h"   // Allows us to use the WaveformSample struct
#include "io.h"         // Header file for this module


// Function that loads CSV data into a dynamically allocated array
int loadCSV(const char *filename, WaveformSample **samples)
{

    // FILE pointer used to access the file
    FILE *file;

    // Open the file in read mode
    file = fopen(filename, "r");

    // If the file cannot be opened
    if(file == NULL)
    {
        printf("Error: Could not open file.\n");
        return -1;
    }


    // Buffer to store each line read from the file
    char line[256];

    // Skip the header row
    fgets(line, sizeof(line), file);


    // Start with capacity for 1000 samples
    int capacity = 1000;

    // Allocate memory dynamically for the samples
    *samples = malloc(sizeof(WaveformSample) * capacity);

    // Counter to track how many rows we read
    int count = 0;


    // Loop through the file until the end
    while(fgets(line, sizeof(line), file))
    {

        // If we exceed current memory capacity, expand it
        if(count >= capacity)
        {
            capacity *= 2; // Double memory size

            *samples = realloc(*samples, sizeof(WaveformSample) * capacity);
        }


        // Parse the CSV line into struct fields
        scanf(line,
               "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &((*samples)[count].timestamp),
               &((*samples)[count].phaseA),
               &((*samples)[count].phaseB),
               &((*samples)[count].phaseC),
               &((*samples)[count].current),
               &((*samples)[count].frequency),
               &((*samples)[count].powerFactor),
               &((*samples)[count].thd)
        );

        // Move to the next sample
        count++;
    }


    // Close the file once reading is complete
    fclose(file);

    // Return the number of samples loaded
    return count;
}
