#include <stdio.h>
#include <unistd.h>

int main() {
    long maxValueOfCoutingSem = sysconf(_SC_SEM_VALUE_MAX);
    if (maxValueOfCoutingSem == -1) {
        perror("Unable to retrieve maximum value of counting semaphore.");
        exit(1);
    }
    printf("Maximum value of a counting semaphore: %ld\n", maxValueOfCoutingSem);
    return 0;
}