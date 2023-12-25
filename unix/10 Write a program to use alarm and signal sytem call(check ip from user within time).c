#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarmHandler(int signum) {
    printf("Time's up! You didn't enter any input.\n");
}

int main() {
    char input[100];

    printf("Enter your input within 5 seconds:\n");

    // Set the alarm to 5 seconds
    alarm(5);

    // Register signal handler for SIGALRM
    signal(SIGALRM, alarmHandler);

    // Read user input
    fgets(input, sizeof(input), stdin);

    // Disable the alarm
    alarm(0);

    printf("You entered: %s", input);

    return 0;
}


