#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main(){
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("Socket creation failed");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr. sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        printf("Connection failed!");
        exit(0);
    }
    int n;
    char buff[BUFFER_SIZE];
    for(;;){
        bzero(buff, sizeof(buff));
        printf("You: ");
        n = 0;
        while((buff[n++] = getchar())!='\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff,sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("Server: %s", buff);
        if((strncmp(buff, "exit", 4)) == 0){
            printf("Client Exit!\n");
            break;
        }
    }

    close(sockfd);
}

