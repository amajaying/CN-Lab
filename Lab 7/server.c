#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345

void handle_client(int client_socket) {
    char message[1024];
    int bytes_received;

    while (1) {
        bytes_received = recv(client_socket, message, sizeof(message), 0);
        if (bytes_received <= 0) {
            close(client_socket);
            break;
        }

        message[bytes_received] = '\0';
        printf("Received: %s", message);

        char response[1024];
        printf("Enter a response (or 'exit' to close the connection): ");
        fgets(response, sizeof(response), stdin);

        if (strcmp(response, "exit\n") == 0) {
            close(client_socket);
            break;
        }

        send(client_socket, response, strlen(response), 0);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    if (listen(server_socket, 1) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

        if (client_socket == -1) {
            perror("Accepting connection failed");
            continue;
        }

        printf("Client connected\n");

        handle_client(client_socket);
    }

    close(server_socket);

    return 0;
}