#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SERVERPORT 4952
int main()
{
	int sockfd;
	struct sockaddr_in clientaddr;

	int numbytes;
	char arg[30];
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Socket Error!!\n");
		return -1;
	}
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(SERVERPORT);
	clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	memset(clientaddr.sin_zero, '\0', sizeof clientaddr.sin_zero);

	printf("Enter a message\n");
	gets(arg);
	if (sendto(sockfd, arg, strlen(arg), 0, (struct sockaddr *)&clientaddr, sizeof clientaddr) < 0)
	{
		printf("Error!!\n");
		return -1;
	}

	close(sockfd);
	return 0;
}