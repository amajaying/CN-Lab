#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

float calculate(float op1, float op2, char opr){
    switch (opr)
    {
    case '+':
        return op1+op2;
        break;
    
    case '-':
        return op1-op2;
        break;
    
    case '*':
        return op1*op2;
        break;
    
    case '/':
        return op1/op2;
        break;
    
    default:
        break;
    }
}

int main()
{
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


    for (;;)
    {
        char menu[] = "1. Addition (+)\n2. Subtraction (-)\n3. Multiplication (*)\n4. Division (/)\n5. Exit\n";
        send(connfd, menu, strlen(menu),0);

        char buff[BUFFER_SIZE];
        memset(buff,0,sizeof(buff));

        if(recv(connfd,buff, sizeof(buff),0)<0)
            break;
        
        if(strcmp(buff,"exit")==0){
            printf("Client wants to exit...\n");
            send(connfd, "Exited!", sizeof("Exited!"),0);
            break;
        }

        char opr;
        sscanf(buff, "%c", &opr);
        if(opr!='+' && opr!='-' && opr!='*' && opr!='/'){
            send(connfd, "Invalid operator!", sizeof("Invalid Operator!"), 0);
            continue;
        }

        float op1, op2;
        memset(buff,0,sizeof(buff));
        if(recv(connfd, buff, sizeof(buff),0)<=0)
            break;
        sscanf(buff,"%f", &op1);
        
        memset(buff,0,sizeof(buff));
        if(recv(connfd, buff, sizeof(buff),0)<=0)
            break;
        sscanf(buff,"%f", &op2);

        double res =calculate(op1,op2,opr);
        printf("%2f",res);
        char result[BUFFER_SIZE];
        sprintf(result, "%.2f", res);
        send(connfd, result, sizeof(result), 0);  
        memset(buff,0,sizeof(buff));      
    }

    close(sockfd);
}