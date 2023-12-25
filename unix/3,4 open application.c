#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
int pid;
pid = fork(); // fork() system call is used to create a new child process
if (pid == 0)
{
printf("Child process is created..\n");
execlp("/snap/bin/firefox", "firefox", NULL); // execlp() system call is used to execute ls command
}
else if (pid < 0)
{
printf("Error in creating child process..\n");
}
else
{
printf("Parent process is created..\n");
wait(NULL); // wait() system call is used to wait for child process to complete
printf("Child process is completed..\n");
}
return 0;
}

