/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Five reader.c

Process reads messages from shared memory
sent from the writer.

Note* Writer must be started before reader
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/stat.h>

struct shared_memory {
    int flag;
    char buffer[1024];
};

struct shared_memory *shared_mem;
int shmid;

void signal_handler(int sig);

int main() {
    key_t key;

    signal(SIGINT, signal_handler);

    if ((key = ftok("writer.c", 'R')) == -1) {
        perror("Unable to assign key\n");
        exit(1);
    }

    // 0666 to allows read and write permissions
    if ((shmid = shmget(key, sizeof(struct shared_memory), 0666)) == -1) {
        perror ("Unable to get shared memory\n");
        exit(1);
    }

    if ((shared_mem = (struct shared_memory *)shmat(shmid, NULL, 0)) == (struct shared_memory *)-1) {
        perror ("Unable to attach\n");
        exit(1);
    }
    
    printf("Reader listening. Press Ctrl+C to exit.\n");

    while (1) {
        if (shared_mem->flag == 1) {
            printf("Received string: %s", shared_mem->buffer);

            // Write turn
            shared_mem->flag = 0;
        }
    }

    return 0;
}

void signal_handler(int sig) {
    
    if (sig == SIGINT){
        printf(" Received shutting down.\n");
    }

    if(shmdt (shared_mem) < 0) {
        perror ("Unable to detach\n");
        exit (1);
    }


    struct shmid_ds shmid_ds;
    if (shmctl(shmid, IPC_STAT, &shmid_ds) == -1) {
        printf("Shared memory already deallocated");
        exit(0);
    }

    if(shmctl (shmid, IPC_RMID, 0) < 0) {
        perror ("Unable to deallocate\n");
        exit(1);
    }

    exit(0);
}