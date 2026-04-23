//
// Created by r2-ngimbimombo on 12/04/2026.
//

#ifndef WAVEFORM_H
#define WAVEFORM_H

typedef struct {

    double timestamp;
    double phaseA;
    double phaseB;
    double phaseC;
    double current;
    double frequency;
    double powerFactor;
    double thd;

} WaveformSample;


// Function prototypes
double calculateRMS(double *data, int n);
double calculatePeakToPeak(double *data, int n);
double calculateMean(double *data, int n);
int detectClipping(double *data, int n);

#endif