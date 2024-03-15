/*****************************************
Brandon Baker, Brendan Coffman
Dr. Bobeldyk
Operating Systems Concepts
Lab Nine memoryMapping.c

Code used to show logical address space of 
different portions of the program.
******************************************/
#include <stdio.h>
#include <stdlib.h>

int globalVar = 10;
int uninitGlobalVar;

void createStackFrames(int depth);

int main() {
    printf("Stack Start\n");
    createStackFrames(0);

    int *dynamicVar = malloc(sizeof(int));
    int *dynamicVar2 = malloc(sizeof(int));

    printf("Heap Variable 2: %p\n", dynamicVar2);
    printf("Heap Variable: %p\n", dynamicVar);
    printf("Uninitialized Global Variable (Data Segment): %p\n", &uninitGlobalVar);
    printf("Global Variable (Data Segment): %p\n", &globalVar);
    printf("Program (Text Segment): %p\n", main);

    free(dynamicVar);
    free(dynamicVar2);
    return 0;
}

void createStackFrames(int depth) {
    char tempVar;
    printf("tempVar at call %d: %p\n", depth, &tempVar);
    if (depth < 5) {
        createStackFrames(depth + 1);
    }
}