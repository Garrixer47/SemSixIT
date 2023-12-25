#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

void convert_to_lowercase(int pipe_read) {
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(pipe_read, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            buffer[i] = tolower(buffer[i]);
        }

        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(pipe_read);
}

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(pipefd[0]);  // Close the unused read end of the pipe

        FILE *input_file;

        if (argc > 1) {
            input_file = fopen(argv[1], "r");
            if (input_file == NULL) {
                perror("fopen");
                return 1;
            }
        } else {
            // Read from stdin
            input_file = stdin;
        }

        char buffer[1024];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
            write(pipefd[1], buffer, bytes_read);
        }

        close(pipefd[1]);
        fclose(input_file);

        wait(NULL);  // Wait for the child process to complete

    } else {
        // Child process
        close(pipefd[1]);  // Close the unused write end of the pipe

        convert_to_lowercase(pipefd[0]);

        close(pipefd[0]);

        return 0;
    }

    return 0;
}

