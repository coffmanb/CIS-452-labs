/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number1.c

Question 1 in Lab 7
******************************************/
#include <stdio.h>
#include <unistd.h>

int main() {
    long maxSemsPerProcess = sysconf(_SC_SEM_NSEMS_MAX);
    if (maxSemsPerProcess == -1) {
        perror("Unable to retrieve maximum semiphores per process.");
        exit(1);
    }
    printf("Maximum number of semaphores per process: %ld\n", maxSemsPerProcess);
    return 0;
}