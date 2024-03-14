/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number5.c

Question 5 in Lab 7
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long pageSize;

    pageSize = sysconf(_SC_PAGESIZE);
    if (sysconf(_SC_PAGESIZE) == -1) {
        perror("Unable to retreive page size");
        exit(1);
    }

    printf("Page size in bytes: %ld\n", pageSize);
    return 0;
}
