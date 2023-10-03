#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

void calculate_characters_and_words(char* text, int* num_characters, int* num_words) {
    *num_characters = strlen(text);
    
    int is_word = 0;
    *num_words = 0;
    for (int i = 0; i < *num_characters; i++) {
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n') {
            is_word = 0;
        } else if (is_word == 0) {
            is_word = 1;
            (*num_words)++;
        }
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }



    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    

    while (1) {
       
        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            perror("Receive error or connection closed");
            break;
        }

        buffer[bytes_received] = '\0';

        int num_characters, num_words;
        calculate_characters_and_words(buffer, &num_characters, &num_words);

        char result[BUFFER_SIZE];
        snprintf(result, BUFFER_SIZE, "Characters: %d, Words: %d", num_characters, num_words);

        
        send(client_socket, result, strlen(result), 0);
    }

   
    close(client_socket);
    close(server_socket);

    return 0;
}