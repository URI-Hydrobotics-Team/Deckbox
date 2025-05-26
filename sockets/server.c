#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main(){
    char buffer[1024] = {0};

    // Variale to store address informaion
    struct sockaddr_in address;
    address.sin_port = htons(8080);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    // Initialize socket
    // AF_INET = IPV4
    // Sock_STREAM = TCP socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Check for socket creation
    if(!server_socket){
        printf("Socket creation failed...\n");
        return -1;
    };
    printf("Socket created successfully\n");

    // Check if the sever can be bind with the address infomration, such as port and etc. 
    if(bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        printf("Socket binding unsuccessful...\n");
        return -1;
    };

    printf("Socket bind successfully\n");

    // Listen to connections made to server, 5 at most
    listen(server_socket, 5);

    socklen_t address_length = sizeof(address);
    memset(&address, 0, address_length);

    int newsocket = accept(server_socket, (struct sockaddr *)&address, &address_length);

    while(1){
        if(newsocket < 0){
            printf("No connections....\n");
            return -1;
        };

        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));
        // Write the received data into the buffer and keep track of the size of the received data
        ssize_t received = read(newsocket, buffer, sizeof(buffer) - 1);
        buffer[received] = '\0';

        // If size of data is 0
        if(received == 0){
            printf("No more messages received, disconnecting....\n");
            close(newsocket);
            break;
        }

        // If there is error when reading data
        else if(received <= -1){
            printf("Errow with socket....\n");
            close(newsocket);
            break;
        }

        else{
            // Print out the received value
            printf("Received: %s\n", buffer);
            printf("\n");
            // Send it back to the client
            write(newsocket, buffer, received - 1);
            printf("Message sented back to client...\n");
        }
    }
}