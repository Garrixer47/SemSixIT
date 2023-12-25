#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    printf("Parent process (PID: %d)\n", getpid());

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) created\n", getpid());
        printf("Child process (PID: %d) exiting with status 42\n", getpid());
        exit(42);
    } else {
        // Parent process
        printf("Parent process (PID: %d) waiting for child (PID: %d) to exit\n", getpid(), pid);
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status: %d\n", pid, WEXITSTATUS(status));
        }
        printf("Parent process (PID: %d) resumed after child (PID: %d) exited\n", getpid(), pid);
    }

    return 0;
}
