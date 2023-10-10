
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    char message[1024];
    char response[1024];

    while (1) {
        printf("Client 2: Enter a message (or 'exit' to close the connection): ");
        fgets(message, sizeof(message), stdin);

        send(client_socket, message, strlen(message), 0);

        if (strcmp(message, "exit\n") == 0) {
            break; 
        }

        int bytes_received = recv(client_socket, response, sizeof(response), 0);
        if (bytes_received <= 0) {
           
            break;
        }

        response[bytes_received] = '\0';
        printf("Server: %s", response);
    }

    
    close(client_socket);

    return 0;
}