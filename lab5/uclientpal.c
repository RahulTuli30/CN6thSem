#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int sockfd, retval;
	int sentbytes, rcvbytes;
	struct sockaddr_in serveraddr;
	char buffer[100];
	socklen_t actlen;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		printf("\nSocket nahi bana.");
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	actlen = sizeof(serveraddr);
	printf("Enter the text.\n");
	scanf("%s",buffer);
	while(strcmp(buffer, "stop")!=0)
	{
		sentbytes = sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if(sentbytes == -1)
		{
			printf("\nOops.");
			close(sockfd);
		}
		rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, &actlen);
		puts(buffer);
		printf("\n");
		printf("Enter another word to check or stop to stop.\n");
		scanf("%s",buffer);
	}
	sentbytes = sendto(sockfd, "stop", sizeof("stop"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if(sentbytes == -1)
		{
			printf("\nOops.");
			close(sockfd);
		}
	close(sockfd);
}
