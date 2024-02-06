#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/wait.h>

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

int nodeCount;

void sigHandler();
void createChildrenNodes(int numNodes, node_t *parentNode, node_t *rootNode);
void processApple(node_t node);


int main() {
    signal(SIGINT, sigHandler);
    int numNodes;
    int toNode;
    apple_t apple;

    printf("How many nodes would you like to create? ");
    fflush(stdout);
    scanf("%d", &nodeCount);
    getchar();

    node_t root;
    root.id = 0;
    if (pipe(root.forward) == -1 || pipe(root.receive) == -1) {
        perror("Failed pipe creation\n");
        exit(1);
    }

    createChildrenNodes(nodeCount, &root, &root);
    close(root.receive[WRITE]);

    while (1) {
        printf("Which node would you like to write to? ");
        fflush(stdout);
        scanf("%d", &toNode);

        printf("Enter a message: ");
        fflush(stdout);
        scanf(" %[^\n]", apple.message); // Read until newline character

        // Send the apple to the specified node
        apple.header = toNode;
        write(root.forward[WRITE], &apple, sizeof(apple_t));

        // Receive the apple back
        read(root.receive[READ], &apple, sizeof(apple_t));
        printf("Root received the apple back. Apple message: %s\n", strlen(apple.message) > 0 ? apple.message : "empty");
    }
}

void processApple(node_t node) {
    
    // Listen for the apple and check whether it belongs
    pid_t pid = fork();
    if(pid == 0) //child
    {
        while(1)
        {
            apple_t apple;
            int bytesRead = read(node.receive[READ], &apple, sizeof(apple_t));
            if(apple.header == node.id){
                printf("Apple belongs to %d reading: %s\n", node.id, apple.message);

                // Clears the message out
                memset(apple.message, 0, sizeof(apple.message));
                printf("Apple message has been cleared\n");
            }

            // Pass apple to next node
            printf("Node: %d has sent the Apple to Node: %d\n", node.id, node.id == nodeCount ? 0 : node.id + 1);
            write(node.forward[WRITE], &apple, sizeof(apple_t)); 
        }
    }
    exit(1);
}

void createChildrenNodes(int numNodes, node_t *parentNode, node_t *rootNode)
{

    node_t newNode;
    newNode.id = numNodes;
    if(numNodes == 1)
    {
        pid_t pid = fork();
        if(pid == 0) //child
        {
            memcpy(newNode.receive, rootNode->forward, sizeof(newNode.receive));
            memcpy(newNode.forward, parentNode->receive, sizeof(newNode.forward));
            printf("Created node %d\n", newNode.id);
            processApple(newNode);
        }
        return;
    }

    pid_t pid = fork();
    if(pid == 0) //child
    {
        memcpy(newNode.forward, parentNode->receive, sizeof(newNode.forward));
        pipe(newNode.receive);
        printf("Created node %d\n", newNode.id);
        createChildrenNodes(numNodes - 1, &newNode, rootNode);
        processApple(newNode);
    }
    wait(&pid);
}

void sigHandler()
{
    printf(" received shutting down\n");
    exit(0);    
}