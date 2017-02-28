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
	socklen_t actlen;
	char buffer[100], find[100], rep[100];
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		printf("\nSocket nahi bana.");
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("Enter the sentence, word to search and word to be replaced with.\n");
	gets(buffer);
	actlen = sizeof(serveraddr);
	//while(strcmp(buffer, "stop")!=0)
	{
		scanf("%s",find);
		scanf("%s",rep);
		sentbytes = sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if(sentbytes == -1)
		{
			printf("\nOops.");
			close(sockfd);
		}
		sentbytes = sendto(sockfd, find, sizeof(find), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if(sentbytes == -1)
		{
			printf("\nOops.");
			close(sockfd);
		}
		sentbytes = sendto(sockfd, rep, sizeof(rep), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if(sentbytes == -1)
		{
			printf("\nOops.");
			close(sockfd);
		}
		rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, &actlen);
		puts(buffer);
		printf("\n");
		//printf("Enter another sentence or stop to stop.\n");
		//gets(buffer);
	}
		sentbytes = sendto(sockfd, "stop", sizeof("stop"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if(sentbytes == -1)
		{
			printf("\nOops.");
			close(sockfd);
		}
	close(sockfd);
}
