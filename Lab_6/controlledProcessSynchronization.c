/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Six controlledProcessSynchronization.c

Program uses semaphore to synchronize use of
shared memory segment between parent and child
processes.
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

#define SIZE 16

int main(int argc, char *argv[])
{
    int status;
    long int i, loop, temp, *sharedMemoryPointer;
    int sharedMemoryID, semID;
    pid_t pid;

    struct sembuf p = {0, -1, SEM_UNDO};
    struct sembuf v = {0, 1, SEM_UNDO};

    loop = atoi(argv[1]);

    if ((semID = semget(IPC_PRIVATE, 1, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) {
        perror("Failed to create semaphore");
        exit(1);
    }

    // By initializing to one, only one process can enter C.S. at a time.
    if (semctl(semID, 0, SETVAL, 1) == -1) {
        perror("Failed to initialize semaphore with value of 1");
        exit(1);
    }

    sharedMemoryID = shmget(IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR);
    if(sharedMemoryID < 0) {
        perror ("Unable to obtain shared memory\n");
        exit (1);
    }

    sharedMemoryPointer = shmat(sharedMemoryID, 0, 0);
    if(sharedMemoryPointer == (void*) -1) {
        perror ("Unable to attach\n");
        exit (1);
    }

    sharedMemoryPointer[0] = 0;
    sharedMemoryPointer[1] = 1;

    pid = fork();
    if(pid < 0){
        printf("Fork failed\n");
    }

    if(pid == 0) { // Child

        // Wait for resource to be available from parent signal.
        if (semop(semID, &p, 1) == -1) {
            perror("Semaphore wait failed in child");
            exit(1);
        }

        for(i=0; i<loop; i++) {
            temp = sharedMemoryPointer[0];
            sharedMemoryPointer[0] = sharedMemoryPointer[1];
            sharedMemoryPointer[1] = temp;
        }

        if(shmdt(sharedMemoryPointer) < 0) {
            perror ("Unable to detach\n");
            exit (1);
        }

        // Free resource.
        if (semop(semID, &v, 1) == -1) {
            perror("Semaphore signal failed in child");
            exit(1);
        }

        exit(0);
    }
    else

        // Parent process runs, decrements semaphore to 0 (no more resources now)
        if (semop(semID, &p, 1) == -1) {
            perror("Semaphore wait failed in parent");
            exit(1);
        }

        for(i=0; i<loop; i++) {
            temp = sharedMemoryPointer[0];
            sharedMemoryPointer[0] = sharedMemoryPointer[1];
            sharedMemoryPointer[1] = temp;
        }

        // Signal ends use of semaphore in parent. Resource available for child.
        if (semop(semID, &v, 1) == -1) {
            perror("Semaphore signal failed in parent");
            exit(1);
        }

        // Wait for child to finish C.S.
        wait(&status);
        printf("Values: %li\t%li\n", sharedMemoryPointer[0], sharedMemoryPointer[1]);
        
        if(shmdt(sharedMemoryPointer) < 0) {
            perror ("Unable to detach\n");
            exit (1);
        }

        if(shmctl(sharedMemoryID, IPC_RMID, 0) < 0) {
            perror ("Unable to deallocate\n");
            exit(1);
        }

        if (semctl(semID, 0, IPC_RMID) == -1) {
            perror("Semaphore deallocation failed");
            exit(1);
        }

    return 0;
}