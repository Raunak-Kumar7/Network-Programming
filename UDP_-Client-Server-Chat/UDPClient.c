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
void func(int sockfd,struct sockaddr_in servaddr)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
	int n, len;	
	sendto(sockfd, (char *)buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
		bzero(buff, sizeof(buff));
	n = recvfrom(sockfd, (char *)buff, MAX, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
		printf("From Server : %s", buff);
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}
int main() {
	int sockfd;
	struct sockaddr_in	 servaddr;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( (sockfd) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr, 0, sizeof(servaddr));	

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	func(sockfd,servaddr);	
	
	close(sockfd);
	return 0;
}
