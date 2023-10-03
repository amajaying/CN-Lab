#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter a text message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        send(sockfd, buffer, strlen(buffer), 0);

        ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            perror("Receive error or connection closed");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Server response: %s\n", buffer);
    }

    close(sockfd);

    return 0;
}