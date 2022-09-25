#include <fcntl.h>  
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

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
		recv(co,buff,sizeof(buff),0);
		printf("From Client %s\t",buff);
		if((strncmp(buff,"exit",4))==0)
		{
			printf("Server exits\n");
			break;
		}
		int flag=0;
		for(int i=0;i<sizeof(buff);i++)
		{
			if(buff[i]=='.')
			{
				flag=1;
				break;
			}
		}
		bzero(buff,MAX);
		if(flag==0)
		{
			buff[0]='i';
		}
		else
		{
			buff[0]='f';
		}
		send(co,buff,sizeof(buff),0);
	}
}
int main()
{
	int sockfd, connfd, len;
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	func(connfd);

	close(sockfd);
}
