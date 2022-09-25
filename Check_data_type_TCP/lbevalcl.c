#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int co)
{
	int n;
	char buff[MAX];
	for(;;)
	{
		n=0;
		bzero(buff,MAX);
		while((buff[n++]=getchar())!='\n')
			;
		send(co,buff,sizeof(buff),0);
		
		bzero(buff,MAX);
		recv(co,buff,sizeof(buff),0);
		if((strncmp(buff,"i",1))==0)
		{
			printf("integer\n");
		}
		else if((strncmp(buff,"f",1))==0)
		{
			printf("float\n");
		}
		if((strncmp(buff,"exit",1))==0)
		{
			printf("client exits\n");
			break;
		}
		
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	func(sockfd);

	close(sockfd);
}
