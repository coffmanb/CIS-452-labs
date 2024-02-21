#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>

int main() {
    int semID;

    if ((semID = semget(IPC_PRIVATE, 1, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) {
        perror("Failed to create semaphore.");
        exit(1);
    }

    struct sembuf semOp = {0, 0, 0};
    if (semop(semID, &semOp, 1) == -1) {
        perror("Failed to perform semaphore operation.");
        exit(1);
    }

    int i;
    for (i = 0; i < 1000000000; i++) {
        semOp.sem_op = 1;
        if (semop(semID, &semOp, 1) == -1) {
            break;
        }
    }

    printf("Maximum value of a counting semaphore: %d\n", i);

    if (semctl(semID, 0, IPC_RMID) == -1) {
        perror("Semaphore deallocation failed.");
        exit(1);
    }

    return 0;
}
