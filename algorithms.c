#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "algorithms.h"

void parseInput(int argc, char *argv[], int *requests, int *numRequests) {
    if (argc > 1) {
        char *token = strtok(argv[1], ",");
        while (token != NULL) {
            requests[*numRequests] = atoi(token);
            (*numRequests)++;
            token = strtok(NULL, ",");
        }
    } else {
        // Generate random requests
        *numRequests = MAX_REQUESTS;
        for (int i = 0; i < MAX_REQUESTS; i++) {
            requests[i] = rand() % MAX_TRACKS;
        }
    }
}

int absDiff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

void SSTF(int *requests, int numRequests, int start) {
    int processed[MAX_REQUESTS] = {0};
    int currentPosition = start;
    int totalTracks = 0;

    for (int i = 0; i < numRequests; i++) {
        int closest = -1;
        int minDistance = MAX_TRACKS;

        for (int j = 0; j < numRequests; j++) {
            if (!processed[j] && absDiff(currentPosition, requests[j]) < minDistance) {
                closest = j;
                minDistance = absDiff(currentPosition, requests[j]);
            }
        }

        if (closest != -1) {
            totalTracks += minDistance;
            currentPosition = requests[closest];
            processed[closest] = 1;
        }
    }

    printf("Total tracks traversed in SSTF: %d\n", totalTracks);
}

