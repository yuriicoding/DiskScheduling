#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {

    int requests[MAX_REQUESTS];

    parseInput(argc, argv, requests);
    SSTF(requests);
    CSCAN(requests);

    return 0;
}
