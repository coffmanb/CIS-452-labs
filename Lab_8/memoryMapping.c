#include <stdio.h>
#include <stdlib.h>

int globalVar = 10;

void createStackFrames(int depth);

int main() {
    

    printf("Stack Start\n");
    createStackFrames(0);

    int *dynamicVar = malloc(sizeof(int));
    int *dynamicVar2 = malloc(sizeof(int));

    printf("Heap variable 2: %p\n", dynamicVar2);
    printf("Heap variable: %p\n", dynamicVar);
    printf("Global variable (Data Segment): %p\n", &globalVar);
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