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