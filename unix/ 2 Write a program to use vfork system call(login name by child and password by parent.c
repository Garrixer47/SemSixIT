#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t childPid;
    char loginName[100];
    char password[100];

    childPid = vfork();

    if (childPid == -1) {
        // Error occurred while forking
        perror("vfork");
        exit(EXIT_FAILURE);
    } else if (childPid == 0) {
        // Child process
        printf("Child: Enter your login name: ");
        scanf("%s", loginName);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent: Enter your password: ");
        scanf("%s", password);
        wait(NULL);
    }

    printf("Child login name: %s\n", loginName);
    printf("Parent password: %s\n", password);

    return 0;
}

