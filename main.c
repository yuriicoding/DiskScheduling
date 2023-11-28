#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    // int *requests = (int *)malloc(MAX_REQUESTS);
    int requests[MAX_REQUESTS];
    int numRequests = 0;
    int sstfOrder[MAX_REQUESTS];
    int cScanOrder[MAX_REQUESTS];
    int longestDelay;
    float averageDelay;

    parseInput(argc, argv, requests, &numRequests);
    int startPosition = requests[0];

    // SSTF 
    SSTF(requests, numRequests, startPosition, sstfOrder, &longestDelay, &averageDelay);

    printf("SSTF Ordered Sequence: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", sstfOrder[i]);
    }
    printf("\n");

    CSCAN(requests, numRequests, startPosition, cScanOrder, &longestDelay, &averageDelay);

    //CSCAN
    printf("CSCAN Ordered Sequence: ");
    for (int i = 0; i < numRequests; i++) {
        printf("%d ", cScanOrder[i]);
    }
    printf("\n");

    return 0;
}
