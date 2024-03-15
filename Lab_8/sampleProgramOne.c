/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Nine sampleProgramOne.c

Program fixes original buffer overflow issue
with scanf function.
******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

int main()
{
    char* data1;

    data1 = malloc(SIZE);
    printf("Please input username: ");
    fgets(data1, SIZE, stdin);
    while(data1[strlen(data1)-1] != '\n')
    {
        char *tempData1 = malloc(strlen(data1) + SIZE);
        memcpy(tempData1,data1,strlen(data1));
        free(data1);
        data1 = tempData1;
        fgets(data1 + strlen(data1), SIZE, stdin);
    }
    data1[strlen(data1)-1] = '\0';
    printf("You entered: [%s]\n", data1);
    free(data1);
    return 0;
}
