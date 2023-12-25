#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Example 1: execl
    printf("execl example:\n");
    execl("/bin/ls", "ls", "-l", NULL);

    // Example 2: execv
    printf("\nexecv example:\n");
    char *args[] = {"/bin/ls", "-l", NULL};
    execv(args[0], args);

    // Example 3: execle
    printf("\nexecle example:\n");
    char *env[] = {"HOME=/usr/home", "USER=guest", NULL};
    execle("/bin/ls", "ls", "-l", NULL, env);

    // Example 4: execve
    printf("\nexecve example:\n");
    char *argv[] = {"/bin/ls", "-l", NULL};
    execve("/bin/ls", argv, env);

    // Example 5: execlp
    printf("\nexeclp example:\n");
    execlp("ls", "ls", "-l", NULL);

    // Example 6: execvp
    printf("\nexecvp example:\n");
    char *cmd[] = {"ls", "-l", NULL};
    execvp(cmd[0], cmd);

    return 0;
}
