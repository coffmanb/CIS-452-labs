#include <stdio.h>
#include <stdlib.h>

// Global variable initialized in data segment
int global_data = 10;

// Function to recursively allocate memory on the stack
void recursive_function(int depth) {
    char stack_variable;
    printf("Stack variable at depth %d: %p\n", depth, &stack_variable);
    if (depth > 0) {
        recursive_function(depth - 1);
    }
}

int main() {
    // Text segment
    printf("Code segment (text): %p\n", (void*) main);

    // Heap segment
    int *heap_variable = malloc(sizeof(int));
    printf("Heap variable: %p\n", (void*) heap_variable);

    // Data segment
    printf("Global variable (data): %p\n", (void*) &global_data);
    
    // Stack segment
    recursive_function(5);

    // Free dynamically allocated memory
    free(heap_variable);

    return 0;
}