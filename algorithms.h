#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#define MAX_TRACKS 200
#define MAX_REQUESTS 200
#define MIN_REQUESTS 50

void parseInput(int argc, char *argv[], int *requests);

void SSTF(int *requests);
void CSCAN(int *requests);

#endif