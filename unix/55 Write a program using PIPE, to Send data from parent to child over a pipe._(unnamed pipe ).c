#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main() {
int pipefd[2];
pid_t pid;
char buffer[BUFFER_SIZE];
const char *message = "Hello from parent";
// Create a pipe
if (pipe(pipefd) == -1) {
perror("pipe failed");
exit(EXIT_FAILURE);
}
// Fork a child process
pid = fork();
if (pid < 0) {
perror("fork failed");
exit(EXIT_FAILURE);
}
if (pid > 0) {
// Parent process
// Close the read end of the pipe
close(pipefd[0]);
// Write data to the pipe
write(pipefd[1], message, strlen(message) + 1);
printf("Parent: Sent message to child\n");
// Close the write end of the pipe
close(pipefd[1]);
// Wait for the child process to exit
wait(NULL);
} else {
// Child process
// Close the write end of the pipe
close(pipefd[1]);
// Read data from the pipe
read(pipefd[0], buffer, BUFFER_SIZE);
printf("Child: Received message from parent: %s\n", buffer);
// Close the read end of the pipe
close(pipefd[0]);
exit(EXIT_SUCCESS);
}
return 0;
}