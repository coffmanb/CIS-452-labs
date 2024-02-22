#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    int sharedMemoryID;
    int size = 1;
    struct shmid_ds shm_ds;

    sharedMemoryID = shmget(IPC_PRIVATE, size, IPC_CREAT|S_IRUSR|S_IWUSR);
    if(sharedMemoryID < 0) {
        perror ("Unable to obtain shared memory\n");
        exit (1);
    }

    // Try to increase the size of the shared memory segment until it fails
    while (shmctl(sharedMemoryID, IPC_STAT, &shm_ds) != -1) {
        size++;
        if (shmctl(sharedMemoryID, IPC_RMID, NULL) == -1) {
            perror("Unable to remove previous shared mem segment.");
            exit(1);
        }
        sharedMemoryID = shmget(IPC_PRIVATE, size, IPC_CREAT|S_IRUSR|S_IWUSR);
        if (sharedMemoryID == -1) {
            break;
        }
    }

    printf("Maximum size of a shared memory segment: %d bytes\n", size);

    return 0;
}
