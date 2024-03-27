#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <stdbool.h>

#define createItem(name, quantity)                                                  \
    if ((name = semget(IPC_PRIVATE, 1, IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) {     \
        perror("Failed to create semaphore");                                       \
        exit(1);                                                                    \
    }                                                                               \
                                                                                    \
    if (semctl(name, 0, SETVAL, quantity) == -1) {                                  \
        perror("Failed to initialize semaphore with value of 1");                   \
        exit(1);                                                                    \
    }

#define resourceListInit()                   \
    createItem(Mixer, 2)                     \
    createItem(Pantry, 1)                    \
    createItem(Refrigerator, 2)              \
    createItem(Bowl, 3)                      \
    createItem(Spoon, 5)                     \
    createItem(Oven, 1)


typedef enum pantryItems
{
    flour = 0,
    sugar,
    yeast,
    bakingSoda,
    salt,
    cinnamon
} pantryItems_enum;

typedef enum fridgeItems
{
    eggs = 0,
    milk,
    butter
} fridgeItems_enum;

/*
Cookies: Flour, Sugar, Milk, Butter
Pancakes: Flour, Sugar, Baking soda, Salt, Egg, Milk, Butter
Homemade pizza dough: Yeast, Sugar, Salt
Soft Pretzels: Flour, Sugar, Salt, Yeast, BakingSoda, Egg
Cinnamon rolls: Flour, Sugar, Salt, Butter, Eggs, Cinnamon
*/

int Mixer;
int Pantry;
int Refrigerator;
int Bowl;
int Spoon;
int Oven;

bool getIngredientFromRefrigerator(fridgeItems_enum ingredient)
{
    struct sembuf waitOperation = {0, -1, SEM_UNDO}; // Wait operation
    struct sembuf signalOperation = {0, 1, SEM_UNDO}; // Signal operation

    if (semop(Refrigerator, &waitOperation, 1) == -1) {
        perror("Failed to wait on semaphore");
        return false;
    }

    // Access refrigerator here

    if (semop(Refrigerator, &signalOperation, 1) == -1) {
        perror("Failed to signal semaphore");
        return false;
    }

    return true;
}

bool getIngredientFromRefrigerator(fridgeItems_enum ingredient)
{
    struct sembuf waitOperation = {0, -1, SEM_UNDO}; // Wait operation
    struct sembuf signalOperation = {0, 1, SEM_UNDO}; // Signal operation

    if (semop(Refrigerator, &waitOperation, 1) == -1) {
        perror("Failed to wait on semaphore");
        return false;
    }

    // Access refrigerator here

    if (semop(Refrigerator, &signalOperation, 1) == -1) {
        perror("Failed to signal semaphore");
        return false;
    }

    return true;
}

int main(void)
{
    resourceListInit();
    return 0;
}
