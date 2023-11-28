#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#define MAX_TRACKS 200
#define MAX_REQUESTS 5

void parseInput(int argc, char *argv[], int *requests, int *numRequests);

void SSTF(int *requests, int numRequests, int start, int *order, int *longestDelay, float *averageDelay);
void CSCAN(int *requests, int numRequests, int start, int *order, int *longestDelay, float *averageDelay);

#endif