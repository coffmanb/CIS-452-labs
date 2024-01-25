#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main()
{
    int fd[2];
    int pipeCreationResult;
    int pid;
    char myStringOutput[] = "This a test!";
    char myStringInput[50];

    pipeCreationResult = pipe(fd);

    if(pipeCreationResult < 0)
    {
        perror("Failed pipe creation\n");
        exit(1);
    }
    pid = fork();
    if(pid < 0) // Fork failed
    {
        perror("Fork failed");
        exit(1);
    }

    int output = 3;
    int input;
    int bytesRead;

    if(pid == 0) // Child process
    { 
        close(fd[0]);
        write(fd[1], &myStringOutput, strlen(myStringOutput) + 1);
        printf("Child wrote [%s]\n", myStringOutput);
    }
    else
    {
        close(fd[1]);
        bytesRead = read(fd[0], &myStringInput, 50);
        printf("Parent received [%s] from child process\n%d bytes were read\n", myStringInput, bytesRead);
    }
    
    return 0;
}