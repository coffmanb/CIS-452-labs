#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    puts("Enter a command to execute");

    // Max of 100 characters in input line
    char* command = malloc(100);
    int max_char = 100;

    // Read User Input and Tokenize String
    char* userInput = fgets(command, max_char, stdin);
    char* str = strtok(userInput, " ");

    /*
        The following code is from ChatGPT. This line changes the
        newline character at the end of the fgets() string to a NULL
        terminating character. This allows the both params in execvp
        to terminate properly.
    */
    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';
    }

    // Store Tokens in arg array, up to 10 tokens, last element is NULL
    char* args[11];
    int count = 0;
    while (str != NULL && count < 10) {
        args[count] = str;
        str = strtok(NULL, " ");
        count++;
    }

    // last element is NULL
    args[count] = NULL;

    if (count < 1)
    {
        fputs("Usage: must supply a command\n", stderr);
        exit(1);
    }
    puts("Before the exec");
    if (execvp(args[0], &args[0]) < 0)
    {
        perror("exec failed");
        exit(1);
    }
    puts("After the exec");

    free(command);

    return 0;
}