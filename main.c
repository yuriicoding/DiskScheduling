
#include "algorithms.h"
int main(int argc, char *argv[]) {
    int requests[MAX_REQUESTS];
    int numRequests = 0;

    parseInput(argc, argv, requests, &numRequests);

    // Assuming the first request is the start position
    int startPosition = requests[0];

    // Call SSTF or other algorithms
    SSTF(requests, numRequests, startPosition);

    // Implement and call other algorithms similarly...

    return 0;
}
