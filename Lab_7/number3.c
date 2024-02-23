/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Seven number3.c

Question 3 in Lab 7
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <limits.h>
#include <sys/sem.h>

int main() {
    int semID;

    if ((semID = semget(IPC_PRIVATE, 1, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) {
        perror("Failed to create semaphore.");
        exit(1);
    }

    
    if (semctl(semID, 0, SETVAL, 0) == -1) {
        perror("Failed to initialize semaphore with value of 0");
        exit(1);
    }

    struct sembuf semOp = {0, 0, 0};
    long long i;
    for (i = 0; i < 10000000; i++) {
        semOp.sem_op = i;
        if (semop(semID, &semOp, 1) == -1) {
            perror("Failed to perform semaphore wait.");
            break;
        }
    }

    printf("Maximum value of a counting semaphore: %lld\n", i-1);

    if (semctl(semID, 0, IPC_RMID) == -1) {
        perror("Semaphore deallocation failed.");
        exit(1);
    }

    return 0;
}
