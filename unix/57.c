#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe_fds[2];
    pid_t pid;

    // Create the pipe
    if (pipe(pipe_fds) == -1) {
        perror("Failed to create pipe");
        exit(1);
    }

    // Fork the process
    pid = fork();

    if (pid > 0) {
        // Parent process

        // Close the read end of the pipe
        close(pipe_fds[0]);

        // Open the file to be sent
        FILE *file = fopen("ay.txt", "rb");
        if (file == NULL) {
            perror("Failed to open file");
            exit(1);
        }

        // Read the file content and write it to the pipe
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            ssize_t bytes_written = write(pipe_fds[1], buffer, bytes_read);
            if (bytes_written == -1) {
                perror("Failed to write to pipe");
                exit(1);
            }
        }

        // Close the write end of the pipe
        close(pipe_fds[1]);

        // Wait for the child process to finish
        wait(NULL);

        // Close the file
        fclose(file);
    } else if (pid == 0) {
        // Child process

        // Close the write end of the pipe
        close(pipe_fds[1]);

        // Create a new file to store the received data
        FILE *file = fopen("received.txt", "wb");
        if (file == NULL) {
            perror("Failed to create received file");
            exit(1);
        }

        // Read the data from the pipe and write it to the file
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fds[0], buffer, BUFFER_SIZE)) > 0) {
            ssize_t bytes_written = fwrite(buffer, 1, bytes_read, file);
            if (bytes_written == -1) {
                perror("Failed to write to file");
                exit(1);
            }
        }

        // Close the read end of the pipe
        close(pipe_fds[0]);

        // Close the file
        fclose(file);

        // Exit the child process
        exit(0);
    } else {
        // Error forking process
        perror("Failed to fork");
        exit(1);
    }

    return 0;
}

