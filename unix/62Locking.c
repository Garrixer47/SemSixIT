#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
   int fd;
   int result;


   // Open a file for writing
   fd = open("locked_file.txt", O_WRONLY | O_CREAT, 0644);
   if (fd == -1) {
       perror("Failed to open file");
       exit(1);
   }


   // Try to acquire a lock on the file
   result = lockf(fd, F_TLOCK, 0);
   if (result == 0) {
       printf("Lock acquired successfully!\n");


       // Write some content to the locked file
       dprintf(fd, "This is a locked file.\n");


       // Sleep for a few seconds to simulate holding the lock
       sleep(5);


       // Release the lock
       result = lockf(fd, F_ULOCK, 0);
       if (result == 0) {
           printf("Lock released successfully!\n");
       } else {
           perror("Failed to release lock");
       }
   } else {
       perror("Failed to acquire lock");
   }


   // Close the file
   close(fd);


   return 0;
}

