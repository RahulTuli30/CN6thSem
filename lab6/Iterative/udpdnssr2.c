#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#define max 50
struct dnslist{
	char name[50];
	char ip[50];
}a;

int main()
{
	strcpy(a.name,"www.gmail.com");
	strcpy(a.ip,"456.456.789.123");
	int sockfd,newsockfd,k;
	socklen_t actuallen;
	int retval;
	size_t leng;
	char c;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;
	char buff[max],temp[max];
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd==-1)
	{
		printf("\n Socket creation error");
		exit(0);
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3390);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_port=htons(3392);
	clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(retval==-1)
	{
		printf("\n Binding error");
		close(sockfd);
	 	exit(0);
	}
	actuallen=sizeof(clientaddr);
	retval=recvfrom(sockfd,temp,sizeof(temp),0,(struct sockaddr *)&clientaddr,&actuallen);
	puts(temp);
	if(retval==-1)
	{
			close(sockfd);
			exit(0);
	}
	if(strcmp(temp,a.name)==0)
		strcpy(temp,a.ip);
	else
		temp[0]='\0';
	retval=sendto(sockfd,temp,sizeof(temp),0,(struct sockaddr *)&clientaddr,actuallen);
	printf("\n");
	
	close(sockfd);
}

