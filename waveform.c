//
// Created by r2-ngimbimombo on 23/04/2026.
//

#include <stdio.h>
#include <math.h>        // Provides sqrt() for RMS calculation
#include "waveform.h"    // Includes struct definition and function prototypes


// ------------------------------------------------------------
// Function: calculateRMS
// Purpose: Calculates RMS voltage of a waveform
// Formula: RMS = sqrt( (1/N) * sum(x^2) )
// ------------------------------------------------------------
double calculateRMS(double *data, int n)
{
    double sum = 0.0;     // Variable to accumulate squared values

    for(int i = 0; i < n; i++)
    {
        sum += data[i] * data[i];   // Square each value and add it
    }

    double mean = sum / n;          // Divide by number of samples

    return sqrt(mean);              // Take square root to get RMS
}



// ------------------------------------------------------------
// Function: calculatePeakToPeak
// Purpose: Finds difference between max and min voltage
// ------------------------------------------------------------
double calculatePeakToPeak(double *data, int n)
{
    double max = data[0];
    double min = data[0];

    for(int i = 1; i < n; i++)
    {
        if(data[i] > max)
            max = data[i];

        if(data[i] < min)
            min = data[i];
    }

    return max - min;
}



// ------------------------------------------------------------
// Function: calculateMean
// Purpose: Calculates DC offset (average voltage)
// ------------------------------------------------------------
double calculateMean(double *data, int n)
{
    double sum = 0.0;

    for(int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}



// ------------------------------------------------------------
// Function: detectClipping
// Purpose: Detects if voltage reaches sensor limit
// Sensor limit from coursework = ±324.9 V
// ------------------------------------------------------------
int detectClipping(double *data, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(fabs(data[i]) >= 324.9)   // fabs = absolute value
        {
            return 1;   // Clipping detected
        }
    }

    return 0;   // No clipping found
}