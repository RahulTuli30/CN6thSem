#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
	int sockfd, newsockfd, retval;
	socklen_t actlen;
	int rcvbytes, sentbytes;
	struct sockaddr_in serveraddr, clientaddr;
	char buffer[100]; 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
		printf("\nSocket nahi bana.");
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(retval == -1)
	{
		printf("\nBind nahi hua.");
		close(sockfd);
	}
	
	actlen = sizeof(clientaddr);
	
	while(1)
	{
		rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr,&actlen);
		if(rcvbytes == -1)
		{
			close(sockfd);
		}
		if(strcmp(buffer, "stop")==0)
			break;
		puts(buffer);
		printf("\n");
		int x = rand()%50;
		int i, len; char conv[100];
		
		for(i=0;buffer[i]!='\0';i++)
		
		{
			buffer[i]=(int)buffer[i]-x;
		}
		//printf("Sent encrypted message.");
		sentbytes = sendto(sockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&clientaddr,sizeof(clientaddr));
		if(sentbytes == -1)
		{
			close(sockfd);
		}
	}
	close(sockfd);
}
