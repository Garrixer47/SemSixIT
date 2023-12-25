#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void performOperation(int operationNumber) {
    // Perform the operation based on the given operation number
    printf("Child %d: Performing operation %d\n", getpid(), operationNumber);
    // You can replace the below code with the actual operation you want each child to perform
    sleep(2); // Simulating some work by sleeping for 2 seconds
    printf("Child %d: Operation %d completed\n", getpid(), operationNumber);
}

int main() {
    int numChildren = 5;

    for (int i = 1; i <= numChildren; i++) {
        pid_t childPid = fork();

        if (childPid == -1) {
            // Error occurred while forking
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (childPid == 0) {
            // Child process
            performOperation(i);
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < numChildren; i++) {
        wait(NULL);
    }

    printf("All child processes have completed.\n");

    return 0;
}


