#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAX 1024
void func(int sockfd, struct sockaddr_in cliaddr)
{
	char buffer[MAX];
	int n;
	for (;;) {
		bzero(buffer, MAX);

		int len, n;
		len = sizeof(cliaddr); //len is value/result
		n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
	
		printf("From client: %s\t To client : ", buffer);
		bzero(buffer, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buffer[n++] = getchar()) != '\n')
			;
		sendto(sockfd, (char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

		if (strncmp("exit", buffer, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}
int main() {
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( (sockfd) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	//initialize client and server address
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	int status = bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr));
	if (status < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}		
	func(sockfd, cliaddr);
	
	printf("Hello message sent.\n");	
	return 0;
}
