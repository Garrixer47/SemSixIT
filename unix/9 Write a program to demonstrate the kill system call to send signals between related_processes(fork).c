#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signum) {
    printf("Signal received: %d\n", signum);
}

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

        // Register signal handler for SIGUSR1
        signal(SIGUSR1, signalHandler);

        printf("Child process (PID: %d) waiting for signal...\n", getpid());
        pause();

        printf("Child process (PID: %d) exiting\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent process (PID: %d) sending SIGUSR1 signal to child (PID: %d)\n", getpid(), pid);
        sleep(2);
        kill(pid, SIGUSR1);

        printf("Parent process (PID: %d) waiting for child (PID: %d) to exit\n", getpid(), pid);
        wait(&status);
        printf("Parent process (PID: %d) resumed after child (PID: %d) exited\n", getpid(), pid);
    }

    return 0;
}

