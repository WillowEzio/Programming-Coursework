#include <stdio.h>      // Allows printing to the console using printf
#include <stdlib.h>     // Allows dynamic memory functions like malloc and free
#include "waveform.h"   // Includes our struct and waveform analysis functions
#include "io.h"         // Includes functions that read the CSV file


// The main function is the starting point of every C program
int main(int argc, char *argv[])
{

    // argc = number of command line arguments
    // argv = the actual arguments passed to the program

    // Check if the user supplied a filename
    if(argc < 2)
    {
        printf("Usage: program <csv file>\n");
        return 1; // Exit the program with error
    }

    // Create a pointer that will store waveform samples
    WaveformSample *samples;

    // Variable to store how many rows were loaded
    int count;

    // Call the function that loads the CSV file
    // argv[1] is the filename passed to the program
    count = loadCSV(argv[1], &samples);

    // If loading failed
    if(count <= 0)
    {
        printf("Error loading file\n");
        return 1;
    }

    // Print how many samples were loaded
    printf("Loaded %d samples\n", count);


    // Allocate memory for phase voltage arrays
    double *phaseA = malloc(sizeof(double) * count);
    double *phaseB = malloc(sizeof(double) * count);
    double *phaseC = malloc(sizeof(double) * count);

    // Copy data from the struct array into voltage arrays
    for(int i = 0; i < count; i++)
    {
        phaseA[i] = samples[i].phaseA;
        phaseB[i] = samples[i].phaseB;
        phaseC[i] = samples[i].phaseC;
    }


    // Calculate RMS voltage for each phase
    double rmsA = calculateRMS(phaseA, count);
    double rmsB = calculateRMS(phaseB, count);
    double rmsC = calculateRMS(phaseC, count);


    // Calculate peak-to-peak voltage
    double p2pA = calculatePeakToPeak(phaseA, count);
    double p2pB = calculatePeakToPeak(phaseB, count);
    double p2pC = calculatePeakToPeak(phaseC, count);


    // Calculate DC offset (mean value)
    double dcA = calculateMean(phaseA, count);
    double dcB = calculateMean(phaseB, count);
    double dcC = calculateMean(phaseC, count);


    // Detect clipping in each phase
    int clipA = detectClipping(phaseA, count);
    int clipB = detectClipping(phaseB, count);
    int clipC = detectClipping(phaseC, count);


    // Print results to the console
    printf("\nResults:\n");

    printf("Phase A RMS: %lf\n", rmsA);
    printf("Phase B RMS: %lf\n", rmsB);
    printf("Phase C RMS: %lf\n", rmsC);

    printf("Phase A Peak-to-Peak: %lf\n", p2pA);
    printf("Phase B Peak-to-Peak: %lf\n", p2pB);
    printf("Phase C Peak-to-Peak: %lf\n", p2pC);

    printf("Phase A DC Offset: %lf\n", dcA);
    printf("Phase B DC Offset: %lf\n", dcB);
    printf("Phase C DC Offset: %lf\n", dcC);


    // Print clipping status
    printf("Phase A Clipping: %d\n", clipA);
    printf("Phase B Clipping: %d\n", clipB);
    printf("Phase C Clipping: %d\n", clipC);


    // Free dynamically allocated memory
    free(samples);
    free(phaseA);
    free(phaseB);
    free(phaseC);

    // Program finished successfully
    return 0;
}
