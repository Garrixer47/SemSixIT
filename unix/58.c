#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define FIFO_PATH "myfifo"


int main() {
   pid_t pid;
   int fifo_fd;
   FILE *file;
   char buffer[1024];
   ssize_t bytes_read;


   // Create the named pipe (FIFO)
   mkfifo(FIFO_PATH, 0666);


   // Fork the process
   pid = fork();


   if (pid > 0) {
       // Parent process


       // Open the named pipe for writing
       fifo_fd = open(FIFO_PATH, O_WRONLY);
       if (fifo_fd == -1) {
           perror("Failed to open FIFO for writing");
           exit(1);
       }


       // Open the file to be sent
       char filename[256];
       printf("Enter the file name: ");
       scanf("%s", filename);

       file = fopen(filename, "rb");
       if (file == NULL) {
           perror("Failed to open file");
           exit(1);
       }


       // Read the file content and write it to the named pipe
       while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
           ssize_t bytes_written = write(fifo_fd, buffer, bytes_read);
           if (bytes_written == -1) {
               perror("Failed to write to FIFO");
               exit(1);
           }
       }


       // Close the file and named pipe
       fclose(file);
       close(fifo_fd);


       // Wait for the child process to finish
       wait(NULL);


   } else if (pid == 0) {
       // Child process


       // Open the named pipe for reading
       fifo_fd = open(FIFO_PATH, O_RDONLY);
       if (fifo_fd == -1) {
           perror("Failed to open FIFO for reading");
           exit(1);
       }


       // Create a new file to store the received data
       file = fopen("received.txt", "wb");
       if (file == NULL) {
           perror("Failed to create received file");
           exit(1);
       }


       // Read the data from the named pipe and write it to the file
       while ((bytes_read = read(fifo_fd, buffer, sizeof(buffer))) > 0) {
           ssize_t bytes_written = fwrite(buffer, 1, bytes_read, file);
           if (bytes_written == -1) {
               perror("Failed to write to file");
               exit(1);
           }
       }


       // Close the file and named pipe
       fclose(file);
       close(fifo_fd);


       // Exit the child process
       exit(0);


   } else {
       // Error forking process
       perror("Failed to fork");
       exit(1);
   }


   // Remove the named pipe
   unlink(FIFO_PATH);


   return 0;
}


