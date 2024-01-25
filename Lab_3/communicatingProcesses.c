#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

void sigHandler(int);
void installSigHandlers(void);

int main()
{
    int pid;

    pid = fork();
    if(pid < 0) // Fork failed
    {
        perror("Fork failed\n");
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
            kill(getppid(), random ? SIGUSR1 :SIGUSR2);
        }
    }
    else
    {
        installSigHandlers();
        printf("spawned child PID# %d\n", pid);
        while(1)
        {
            printf("waiting...\t");
            fflush(stdout);
            pause();
            installSigHandlers();
        }
    }

    return 0;
}
void installSigHandlers(void)
{
    signal(SIGINT, sigHandler);
    signal(SIGUSR1, sigHandler);
    signal(SIGUSR2, sigHandler);
}

void sigHandler(int sigNum)
{
    if(sigNum == SIGINT)
    {
        printf(" received shutting down\n");
        exit(0);
    }
    else if(sigNum == SIGUSR1)
        printf("received a SIGUSR1 signal.\n");
    else if(sigNum == SIGUSR2)
        printf("received a SIGUSR2 signal.\n");
    else
    {
        printf("unknown condition exiting");
        exit(0);
    }
}
