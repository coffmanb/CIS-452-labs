#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

typedef struct {
    int header;
    char message[100];
} apple_t;

typedef struct {
    int forward[2];
    int receive[2];
    int id;
} node_t;

void createNode(int depth, node_t node);
void processApple(apple_t apple);

int main() {
    int numNodes;
    int toNode;
    apple_t apple;

    printf("How many nodes would you like to create? ");
    fflush(stdout);
    scanf("%d", &numNodes);

    node_t root;
    root.id = 0;

    if (pipe(root.forward) == -1 || pipe(root.receive) == -1) {
        perror("Failed pipe creation\n");
        exit(1);
    }

    pid_t root_pid = getpid();  // Keep track of the root process ID

    createNode(numNodes, root);

    close(root.receive[WRITE]);

    while (1) {
        printf("Which node would you like to write to? ");
        fflush(stdout);
        scanf("%d", &toNode);

        printf("Write a message: ");
        fflush(stdout);
        scanf("%s", apple.message);

        // Send the apple to the specified node
        apple.header = toNode;
        write(root.forward[WRITE], &apple, sizeof(apple_t));

        // Receive the apple back
        read(root.receive[READ], &apple, sizeof(apple_t));
        printf("Root received the apple back: %s\n", apple.message);
    }
}

void processApple(apple_t apple) {
    // Process the received apple if needed
}

void createNode(int depth, node_t node) {
    apple_t apple;
    int bytesRead;

    node.id += 1;

    if (depth >= 1) {
        printf("Node created: %d\n", node.id);

        if (pipe(node.forward) == -1 || pipe(node.receive) == -1) {
            perror("Failed pipe creation\n");
            exit(1);
        }

        createNode(depth - 1, node);

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }
    }

    while (1) {
        bytesRead = read(node.receive[READ], &apple, sizeof(apple_t));
        printf("Node %d received the apple\n", apple.header);

        if (apple.header == node.id) {
            printf("Apple is for this node: %s\n", apple.message);
            // Clear the message
            memset(apple.message, 0, sizeof(apple.message));
        } else {
            // Process the apple if needed
            processApple(apple);

            // Send the apple to the next node
            write(node.forward[WRITE], &apple, sizeof(apple_t));
        }
    }
}
