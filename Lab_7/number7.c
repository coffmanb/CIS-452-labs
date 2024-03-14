/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number7.c

Question 7 in Lab 7
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long maxProcessesPerUser;

    maxProcessesPerUser = sysconf(_SC_CHILD_MAX);
    if (maxProcessesPerUser == -1) {
        perror("Unable to retreive max processes per user");
        exit(1);
    }

    printf("Maximum number of processes per user: %ld\n", maxProcessesPerUser);
    return 0;
}
