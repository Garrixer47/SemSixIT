#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    char *shm, *s;
    FILE *file;

    // Generate a unique key for the shared memory segment
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory segment
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Sender process
    printf("Sender: Enter a sequence of characters/numbers (up to %d): ", SHM_SIZE);
    fgets(shm, SHM_SIZE, stdin);

    // Write to file
    file = fopen("shared_data.txt", "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", shm);
    fclose(file);

    // Detach from the shared memory segment
    shmdt(shm);

    // Receiver process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Attach to the shared memory segment
        shm = shmat(shmid, NULL, 0);
        if (shm == (char *)-1) {
            perror("shmat");
            exit(EXIT_FAILURE);
        }

        // Read from file
        file = fopen("shared_data.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fgets(shm, SHM_SIZE, file);
        fclose(file);

        printf("Receiver: Received sequence: %s", shm);

        // Detach from the shared memory segment
        shmdt(shm);

        // Mark the shared memory segment for deletion
        shmctl(shmid, IPC_RMID, NULL);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}

