/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Five writer.c

Process writes messages to shared memory
to be printed by the reader.

Note* Writer must be started before reader
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/stat.h>

struct shared_memory {
    // Determines whether its time ot read or write
    int flag;

    // Shared mem 1024 bytes long
    char buffer[1024];
};

struct shared_memory *shared_mem;
int shmid = 0;

void signal_handler(int sig);

int main() {
    key_t key;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if ((key = ftok("writer.c", 'R')) == -1) {
        perror("Unable to assign key\n");
        exit(1);
    }

    if ((shmid = shmget(key, sizeof(struct shared_memory), IPC_CREAT|0666)) == -1) {
        perror ("Unable to get shared memory\n");
        exit(1);
    }

    // shmat returns pointer to shared_mem struct
    if ((shared_mem = (struct shared_memory *)shmat(shmid, NULL, 0)) == (struct shared_memory *)-1) {
        perror ("Unable to attach\n");
        exit(1);
    }

    printf("Writer process running. Enter 'quit' or press ^C to exit.\n");

    while (1) {
        printf("Enter a string: ");
        fgets(shared_mem->buffer, 1024, stdin);
        
        if (strncmp(shared_mem->buffer, "quit", 4) == 0) {
            signal_handler(20);
        }

        // Read Turn
        shared_mem->flag = 1;
    }
    return 0;
}

void signal_handler(int sig) {

    if (sig == SIGINT){
        printf("\n^C Recieved shutting down.\n");
    } else if (sig == 20){
        printf("Quit recieved shutting down.\n");
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
