#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

    semid = semget(key, 1, 0);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;

    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    printf("P operation performed successfully.\n");

    return 0;
}

