#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include "algorithms.h"

int numRequests = 0;



void parseInput(int argc, char *argv[], int *requests) {
    if (argc > 1) {
        char *token = strtok(argv[1], ",");
        while (token != NULL) {
            requests[numRequests] = atoi(token);
            (numRequests)++;
            token = strtok(NULL, ",");
        }
    } else {
        // Generate random requests
        numRequests = MAX_REQUESTS;
        srand(time(NULL));
        printf("The original list of tracks: ");
        for (int i = 0; i < MAX_REQUESTS; i++) {
            requests[i] = rand() % MAX_TRACKS;
            printf("%d ", requests[i]);
        }
        printf("\n");
    }
}



int absDiff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}



int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}



void SSTF(int *requests) {
    int startPosition = requests[0];
    int currentPosition = startPosition;

    int order[MAX_REQUESTS];
    int processed[MAX_REQUESTS] = {0};
    int delay[MAX_REQUESTS] = {0};
    int orderIndex = 0;
    
    int totalTracks = 0;
    int totalDelay = 0;
    int longestDelay = 0;
    float averageDelay = 0;
    

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
            order[orderIndex++] = requests[closest]; // Track the order of servicing

            // Calculate delay for the serviced track
            for (int k = 0; k < numRequests; k++) {
                if (requests[k] == requests[closest]) {
                    delay[k] = orderIndex - 1 - k;
                    totalDelay += (delay[k] > 0) ? delay[k] : 0;
                    if (delay[k] > longestDelay) {
                        longestDelay = delay[k];
                    }
                    break;
                }
            }
        }
    }

    // Calculate average delay
    int delayedRequests = 0;
    for (int i = 0; i < numRequests; i++) {
        if (delay[i] > 0) {
            delayedRequests++;
        }
    }
    averageDelay = (delayedRequests > 0) ? (float)totalDelay / delayedRequests : 0.0f;

    printf("\nTotal tracks traversed in SSTF: %d\n", totalTracks);
    printf("Longest Delay in SSTF: %d\n", longestDelay);
    printf("Average Delay in SSTF: %.2f\n", averageDelay);
    printf("SSTF Ordered Sequence: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
}



void CSCAN(int *requests) {
    int startPosition = requests[0];
    int currentPosition = startPosition;

    int order[MAX_REQUESTS];
    int sortedRequests[MAX_REQUESTS];
    int delay[MAX_REQUESTS] = {0};
    int originalPositions[MAX_REQUESTS];
    int orderIndex = 0;

    int totalTracks = 0;
    int totalDelay = 0;
    int longestDelay = 0;
    float averageDelay = 0;

    // Copy and sort the request array; also keep track of original positions
    for (int i = 0; i < numRequests; i++) {
        sortedRequests[i] = requests[i];
        originalPositions[i] = i;
    }
    qsort(sortedRequests, numRequests, sizeof(int), compare);

    // Find start position in sorted array
    int startPos = numRequests - 1;
    while (startPos >= 0 && sortedRequests[startPos] > startPosition) {
        startPos--;
    }

    // Service requests to the left
    for (int i = startPos; i >= 0; i--) {
        totalTracks += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
        order[orderIndex] = sortedRequests[i];

        // Find the original position of this request and calculate delay
        for (int j = 0; j < numRequests; j++) {
            if (requests[j] == sortedRequests[i]) {
                delay[j] = orderIndex - originalPositions[j];
                break;
            }
        }
        orderIndex++;
    }

    // Jump to the rightmost end
    totalTracks += currentPosition; // Moving to track 0
    totalTracks += MAX_TRACKS - 1; // Moving to the highest track
    currentPosition = MAX_TRACKS - 1;

    // Continue servicing the remaining requests
    for (int i = numRequests - 1; i > startPos; i--) {
        totalTracks += abs(sortedRequests[i] - currentPosition);
        currentPosition = sortedRequests[i];
        order[orderIndex] = sortedRequests[i];

        // Update delay
        for (int j = 0; j < numRequests; j++) {
            if (requests[j] == sortedRequests[i]) {
                delay[j] = orderIndex - originalPositions[j];
                break;
            }
        }
        orderIndex++;
    }

    // Calculate longest and average delay
    for (int i = 0; i < numRequests; i++) {
        totalDelay += (delay[i] > 0) ? delay[i] : 0;
        if (delay[i] > longestDelay) {
            longestDelay = delay[i];
        }
    }

    int delayedRequests = 0;
    for (int i = 0; i < numRequests; i++) {
        if (delay[i] > 0) delayedRequests++;
    }
    averageDelay = (delayedRequests > 0) ? (float)totalDelay / delayedRequests : 0.0f;

    printf("\nTotal tracks traversed in C-SCAN (Left to Right): %d\n", totalTracks);
    printf("Longest Delay in C-SCAN: %d\n", longestDelay);
    printf("Average Delay in C-SCAN: %.2f\n", averageDelay);
    printf("CSCAN Ordered Sequence: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
}

