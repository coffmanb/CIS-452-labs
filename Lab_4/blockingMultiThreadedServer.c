#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX_NUM_THREADS 3


typedef struct{
    char filename[100];
    int status; //0 is free 1 is running
}threadStatus_t;

pthread_t threads[MAX_NUM_THREADS];
threadStatus_t threadStatus[MAX_NUM_THREADS];


void sigHandler(int);
void* readFile(void* arg);
int findAvailableThread(threadStatus_t *threadList);


int main() {
    signal(SIGINT, sigHandler);  // Set up signal handler for SIGINT

    char fileName[100];
    while (1) {
        int thread = 0;
        printf("Enter a file name: ");
        fflush(stdout);
        scanf("%s", fileName);

        thread = findAvailableThread(threadStatus);

        threadStatus[thread].status = 1;  // Mark thread as in use
        strcpy(threadStatus[thread].filename, fileName);
        pthread_create(&threads[thread], NULL, readFile, &threadStatus[thread]);
        for(int i = 0; i < MAX_NUM_THREADS; i++)
        {
            printf("thread %d: %d\n", i, threadStatus[i].status);
        }
    }

    return 0;
}

int findAvailableThread(threadStatus_t *threadList)
{
    int thread = 0;
    while (threadList[thread].status == 1) {
        thread++;
        if (thread >= MAX_NUM_THREADS) {
            printf("Maximum number of threads reached.\n");
            sleep(1);
            return findAvailableThread(threadList);
        }
    }
    return thread;
}

void* readFile(void* myArgument)
{
    threadStatus_t* threadInfo = (threadStatus_t*)myArgument;
    int sleepTime = rand() % 5;
    sleep((sleepTime == 0 ? 6 + rand() % 5 : 1));
    printf("Found: %s\n", threadInfo->filename);
    fflush(stdout);
    threadInfo->status = 0;
    return NULL;
}

void sigHandler(int sigNum)
{
    if(sigNum == SIGINT)
    {
        printf(" received shutting down\n");
        int thread = 0;
        // Shut down running threads
        for(int i = 0; i < MAX_NUM_THREADS; i++)
        {
            printf("thread %d: %d", i, threadStatus[i].status);
            if(threadStatus[i].status == 1)
            {
                pthread_join(threads[i], NULL);
            }
        }
        printf("All tasks done!\n");
        exit(0);
    }
}