#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main()
{
    char buff[BUFFER_SIZE];
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed!");
        exit(0);
    }
    else
    {
        printf("Socket created!\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("Socket bind failed!\n");
        exit(0);
    }
    else
    {
        printf("Socket binding successful!\n");
    }

    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed!\n");
        exit(0);
    }
    else
    {
        printf("Server Listening!\n");
    }

    len = sizeof(cliaddr);

    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (connfd < 0)
    {
        printf("Server Accept Failed!\n");
        exit(0);
    }
    else
    {
        printf("Server Accepted the client!\n");
    }

    bzero(buff, BUFFER_SIZE);
    int n;

    for (;;)
    {
        bzero(buff, BUFFER_SIZE);
        read(connfd, buff, sizeof(buff));
        printf("Client: %s", buff);
        bzero(buff, BUFFER_SIZE);
        n = 0;
        printf("You: ");
        while ((buff[n++] = getchar()) != '\n');
        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit!\n");
            break;
        }
    }

    close(sockfd);
}