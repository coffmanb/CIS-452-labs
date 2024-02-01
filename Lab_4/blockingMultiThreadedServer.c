#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX_NUM_THREADS 10
void sigHandler(int);
void* readFile(void* arg);

pthread_t threads[MAX_NUM_THREADS];
int threadStatus[MAX_NUM_THREADS];

int main(){
    
    
    void *result1, *result2;
    int threadStatus1, threadStatus2;
    int joinStatus1, joinStatus2;
    char fileName[100];
    while(1)
    {
        int thread = 0;
        printf("Enter a file name: ");
        fflush(stdout);
        scanf("%s",fileName);

        //Find next available thread
        while(threadStatus[thread] == 1)
        {
            thread++;
        }
        threadStatus1 = pthread_create (&threads[thread], NULL, readFile, fileName);
    }
    return 0;
}

void* readFile(void *myArgument){
    char *myPtr = (char *)myArgument;
    int sleepTime = rand() % 5;
    sleep(sleepTime == 0 ? 6 + rand() % 5 : 1);
    printf("Found: %s\n", myPtr);
    return NULL;
}

void sigHandler(int sigNum)
{
    if(sigNum == SIGINT)
    {
        printf(" received shutting down\n");
        int thread = 0;
        //shut down running threads
        for(int i = 0; i < MAX_NUM_THREADS; i++)
        {
            if (threadStatus[i] == 1)
            {
                pthread_join(&threads[i],NULL);
            }
        }
        exit(0);
    }
}