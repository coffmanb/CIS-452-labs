/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number6.c

Question 6 in Lab 7
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    long physicalPages;

    physicalPages = sysconf(_SC_PHYS_PAGES);
    if (sysconf(_SC_PHYS_PAGES) == -1) {
        perror("Unable to retreive number of physical pages");
        exit(1);
    }

    printf("Physical Pages: %ld\n", physicalPages);
    return 0;
}
