#ifndef ALGORITHMS_H
#define ALGORITHMS_H


#define MAX_TRACKS 200
#define MAX_REQUESTS 50

void parseInput(int argc, char *argv[], int *requests, int *numRequests);

void SSTF(int *requests, int numRequests, int start);

#endif