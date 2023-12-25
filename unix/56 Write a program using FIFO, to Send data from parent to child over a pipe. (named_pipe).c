#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 1024
int main() {
int fd;
pid_t pid;
char buffer[BUFFER_SIZE];
const char* fifoPath = "/tmp/myfifo";
const char* message = "Hello from parent";
// Create the named pipe (FIFO)
if (mkfifo(fifoPath, 0666) == -1) {
perror("mkfifo failed");
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
// Open the named pipe for writing
fd = open(fifoPath, O_WRONLY);
if (fd == -1) {
perror("open failed");
exit(EXIT_FAILURE);
}
// Write data to the named pipe
write(fd, message, strlen(message) + 1);
printf("Parent: Sent message to child\n");
// Close the named pipe
close(fd);
// Wait for the child process to exit
wait(NULL);
} else {
// Child process
// Open the named pipe for reading
fd = open(fifoPath, O_RDONLY);
if (fd == -1) {
perror("open failed");
exit(EXIT_FAILURE);
}
// Read data from the named pipe
read(fd, buffer, BUFFER_SIZE);
printf("Child: Received message from parent: %s\n", buffer);
// Close the named pipe
close(fd);
exit(EXIT_SUCCESS);
}
// Remove the named pipe (FIFO)
unlink(fifoPath);
return 0;
}