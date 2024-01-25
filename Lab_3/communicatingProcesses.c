#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define READ 0
#define WRITE 1

void sigHandler1(int);
void sigHandler2(int);
void installSigHandlers(void);

int main()
{
    int pid;

    pid = fork();
    if(pid < 0) // Fork failed
    {
        perror("Fork failed");
        exit(1);
    }


    if(pid == 0) // Child process
    { 
        int random;
        while(1)
        {
            random = 1 + rand()%4;
            sleep(random);
            random = rand()%2;
            pid = fork();
            if(pid == 0) // Child process
            {
                kill(getpid(), random ? SIGUSR1 :SIGUSR2);
            }
        }
    }
    else
    {
        installSigHandlers();
        printf("spawned child PID# %d", pid);
        while(1)
        {
            printf("waiting...");
            pause();
            installSigHandlers();
        }
    }

    return 0;
}
void installSigHandlers(void)
{
    signal(SIGUSR1,sigHandler1);
    signal(SIGUSR2,sigHandler2);
}
void sigHandler1 (int sigNum)
{
   printf("\treceived a SIGUSR1 signal.\n");
}

void sigHandler2 (int sigNum)
{
    printf("\treceived a SIGUSR2 signal.\n");
}