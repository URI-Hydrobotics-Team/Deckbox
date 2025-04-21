#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Status of the socket connection and the value received from client
    int status, valread;
    struct sockaddr_in address;

    // Create the socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Check for client socket creation
    if(!client_socket) {
        printf("Cannot create client socket");
    };

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    // Contain message that send to server and buffer to store data from server
    char message[1024] = {0};
    char buffer[1024] = {0};

    // Convert IP address to inary form and check if there is error with this process
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) {
        printf("\nInvalid address\n");
        return -1;
    };

    // Check for connection status to the server
    if ((status = connect(client_socket, (struct sockaddr*)&address, sizeof(address))) < 0) {
       printf("\nConnection Failed \n");
       return -1;
   }

    while(1){
        // Clear buffer
        memset(buffer, 0, sizeof(buffer));
        printf("Input the intended values: ");
        // Read user input into message 
        fgets(message, sizeof(message), stdin); 
        printf("\n");
        // Send the message to server
        send(client_socket, message, strlen(message), 0);
        printf("Message sent\n");
        // Read message from server
        valread = read(client_socket, buffer, sizeof(buffer) - 1); 
        printf("From server: %s\n", buffer);
    }

    // closing the connected socket
    close(client_socket);
    return 0;
}