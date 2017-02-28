#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 100
int flag=0;
struct DNS {
    char name[100];
    char IP[100];
   
}db[3];
main()
{
	int sockfd,newsockfd,retval,i;
	socklen_t actuallen;
	int recedbytes,sentbytes;
	struct sockaddr_in serveraddr,clientaddr;

	char buff[MAXSIZE];
	int a=0;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	if(sockfd==-1)
	{
	printf("\nSocket creation error");
	}

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3389);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
	{
	printf("Binding error");
	close(sockfd);
	}
	
	actuallen=sizeof(clientaddr);
	
	recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr, &actuallen);
	
	if(recedbytes==-1)
	{
	close(sockfd);
	}
	strcpy(db[0].name,"www.bing.com");
	strcpy(db[0].IP,"222.122.122.1");
	strcpy(db[1].name,"www.youtube.com");
	strcpy(db[1].IP,"255.1.1.1");
	strcpy(db[2].name,"www.twitter.com");
	strcpy(db[2].IP,"1.255.255.125");
	

	for(i=0;i<3;i++)
	{

		if(strcmp(db[i].name,buff)==0)
			{ flag=1;
				sentbytes=sendto(sockfd,db[i].IP,sizeof(db[i].IP),0,(struct sockaddr*)&clientaddr, sizeof(clientaddr));
	
				if(sentbytes==-1)
					{printf("error from main to local");
					close(sockfd);
					}
			}
	
	}
		if(flag==1){
			strcpy(buff,"NOTFOUND");
			sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr, sizeof(clientaddr));
	
				if(sentbytes==-1)
					{
					close(sockfd);
					}
	
				}
		close(sockfd);
}

