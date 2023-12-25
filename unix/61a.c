#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int semid;
    key_t key;

    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore ID: %d\n", semid);

    return 0;
}

