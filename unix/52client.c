#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket file descriptor
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set server address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary format
    if (inet_pton(AF_INET, SERVER_IP, &(server_addr.sin_addr)) <= 0) {
        perror("Invalid address or address not supported");
        exit(1);
    }

    // Read input from the user
    printf("Enter message: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // Send the message to the server
    sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Receive the server's response
    ssize_t bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, NULL, NULL);
    printf("Server response: %.*s", (int)bytes_received, buffer);

    // Close the socket
    close(client_socket);

    return 0;
}


