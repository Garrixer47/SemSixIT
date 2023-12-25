#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
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

        // Open the file or use standard input
        FILE *file;
        if (argc == 2) {
            file = fopen(argv[1], "r");
            if (file == NULL) {
                perror("Failed to open file");
                exit(1);
            }
        } else {
            file = stdin; // Use standard input
        }

        // Read input and write it to the pipe after converting to lowercase
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                buffer[i] = tolower(buffer[i]);
            }
            ssize_t bytes_written = write(pipe_fds[1], buffer, bytes_read);
            if (bytes_written == -1) {
                perror("Failed to write to pipe");
                exit(1);
            }
        }

        // Close the write end of the pipe
        close(pipe_fds[1]);

        // Close the file or standard input
        if (argc == 2) {
            fclose(file);
        }

        // Wait for the child process to finish
        wait(NULL);
    } else if (pid == 0) {
        // Child process

        // Close the write end of the pipe
        close(pipe_fds[1]);

        // Read data from the pipe and convert to lowercase
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fds[0], buffer, BUFFER_SIZE)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                buffer[i] = tolower(buffer[i]);
            }
            ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
            if (bytes_written == -1) {
                perror("Failed to write to stdout");
                exit(1);
            }
        }

        // Close the read end of the pipe
        close(pipe_fds[0]);

        // Exit the child process
        exit(0);
    } else {
        // Error forking process
        perror("Failed to fork");
        exit(1);
    }

    return 0;
}



