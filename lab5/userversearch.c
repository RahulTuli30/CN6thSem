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
	char buffer[100], find[100], rep[100]; 
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
	
	int n, rn;
	rcvbytes = recvfrom(sockfd, &rn, sizeof(rn), 0, (struct sockaddr*)&clientaddr,&actlen);
	n = ntohl(rn);
	if(rcvbytes == -1)
	{
		close(sockfd);
	}
	int arr[50], ritem, item, flag=0,i;
    	rcvbytes = recvfrom(sockfd, arr, sizeof(arr), 0, (struct sockaddr*)&clientaddr,&actlen);
	if(rcvbytes == -1)
	{
		close(sockfd);
	}
    	rcvbytes = recvfrom(sockfd, &ritem, sizeof(ritem), 0, (struct sockaddr*)&clientaddr,&actlen);
	if(rcvbytes == -1)
	{
		close(sockfd);
	}
	item = ntohl(ritem);
	for(i=0;i<n;i++)
	{
		if(arr[i] == item)
		{
			flag = 1;
			break;
		}
	}
	if(flag)
		sentbytes = sendto(sockfd, "Element found!", sizeof("Element found!"),0, (struct sockaddr*)&clientaddr,sizeof(clientaddr));
	else
		sentbytes = sendto(sockfd, "Element not found!", sizeof("Element not found!"),0, (struct sockaddr*)&clientaddr,sizeof(clientaddr));			
		
	if(sentbytes == -1)
		{
			close(sockfd);
		}	
	
	close(sockfd);
}
