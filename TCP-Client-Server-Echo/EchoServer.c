#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>  //for open
#include <unistd.h> //for close
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int connfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, MAX);

		recv(connfd, buff, sizeof(buff),0);
		printf("From client: %s To client : %s", buff,buff);
		//bzero(buff, MAX);
		//n = 0;
		// copy server message in the buffer
		//while ((buff[n++] = getchar()) != '\n')
		//	;

		send(connfd, buff, sizeof(buff),0);
		//always exit with exit not with ^C, else socket would be already binded
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
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
