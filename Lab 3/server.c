#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MYPORT 4952
#define MAXBUFLEN 200
int main()
{
    printf("Server is waiting for message to receive! \n\n");
    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    socklen_t addr_len;
    int numbytes;
    char buf[MAXBUFLEN];
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Socket Error!!\n");
        return -1;
    }
    addr_len = sizeof clientaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    memset(servaddr.sin_zero, '\0', sizeof(servaddr.sin_zero));

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Binding Error!!\n");
        return -1;
    }
    while (1)
    {
        
        if (recvfrom(sockfd, buf, MAXBUFLEN - 1, 0, (struct sockaddr *)&clientaddr, &addr_len) < 0)
        {
            printf("Error!!\n");
            return -1;
        }

        printf("amajaying: %s\n", buf);
        memset(buf,'\0',sizeof(buf));
        memset(clientaddr.sin_zero, '\0', sizeof clientaddr.sin_zero);
        printf("Enter a message\n");
        gets(buf);
        if (sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clientaddr, sizeof clientaddr) < 0)
        {
            printf("Error!!\n");
            return -1;
        }
        if(strcmp(buf,"exit")==0){
            break;
        }
    }

    close(sockfd);
    return 0;
}