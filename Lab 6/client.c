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
    char buff[BUFFER_SIZE];
    memset(buff,0, sizeof(buff));
    while(1){

        if(recv(sockfd,buff,sizeof(buff),0)<=0)
            break;
        printf("Menu:\n%s\n", buff);

        printf("Enter the operator: ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff,"\n")]=0;
        send(sockfd, buff, sizeof(buff),0);

        if(strcmp(buff, "exit")==0){
            printf("Exiting...\n");
            break;
        }

        printf("Enter Operand 1: ");
        fgets(buff,sizeof(buff),stdin);
        buff[strcspn(buff, "\n")]=0;
        send(sockfd, buff, sizeof(buff),0);

        printf("Enter Operand 2: ");
        fgets(buff,sizeof(buff),stdin);
        buff[strcspn(buff, "\n")]=0;
        send(sockfd, buff, sizeof(buff),0);

        memset(buff,0, sizeof(buff));
        if(recv(sockfd,buff,sizeof(buff),0)<=0)
            break; 
        
        printf("\nResult: %s\n\n", buff);
    }

    close(sockfd);
}

