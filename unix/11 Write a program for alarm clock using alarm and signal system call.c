#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarmHandler(int signum) {
    printf("Alarm! Wake up!\n");
}

int main() {
    int seconds;

    printf("Enter the number of seconds for the alarm: ");
    scanf("%d", &seconds);

    // Register signal handler for SIGALRM
    signal(SIGALRM, alarmHandler);

    printf("Alarm set for %d seconds.\n", seconds);

    // Set the alarm
    alarm(seconds);

    // Sleep until the alarm goes off
    pause();

    printf("Exiting the alarm clock.\n");

    return 0;
}
