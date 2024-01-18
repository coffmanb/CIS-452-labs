#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void getUsageStats(void)
{
    struct rusage usage;
    getrusage(RUSAGE_CHILDREN, &usage);

    printf("CPU time used by the child process: %ld.%06ld seconds\n", 
        usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("involuntary context switches by the child process: %ld\n", 
        usage.ru_nivcsw);
}
int main(void)
{
    // Max of 100 characters in input line
    char* command = malloc(100);
    int max_char = 100;
    
    // Read User Input and Tokenize String
    puts("Enter a command to execute");
    char* userInput = fgets(command, max_char, stdin);

    while(strcmp(userInput, "quit") != 0)
    {
        /*
            The following code to read the input is from ChatGPT. This line changes the
            newline character at the end of the fgets() string to a NULL
            terminating character. This allows the both params in execvp
            to terminate properly.
        */
        char* str = strtok(userInput, " ");
        size_t len = strlen(userInput);
        if (len > 0 && userInput[len - 1] == '\n')
        {
            userInput[len - 1] = '\0';
        }

        // Store Tokens in arg array, up to 10 tokens, last element is NULL
        char* args[11];
        int count = 0;
        while (str != NULL && count < 10)
        {
            args[count] = str;
            str = strtok(NULL, " ");
            count++;
        }

        // last element is NULL
        args[count] = NULL;

        
        pid_t pid;

        if(strcmp(userInput, "quit") == 0)
        {
            break;
        }

        if ((pid = fork()) < 0)
        {
            fprintf(stderr, "Fork failure");
            exit(1);
        }
        else if (pid == 0)
        {
            if (count < 1)
            {
                fputs("Usage: must supply a command\n", stderr);
                exit(1);
            }
            if (execvp(args[0], &args[0]) < 0)
            {
                exit(1);
            }
        }
        else
        {
            wait(&pid);
            getUsageStats();
            puts("Enter a command to execute");
            char* userInput = fgets(command, max_char, stdin);
        }
    }

    return 0;
}