#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

int flag = 0;

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
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(retval==1)
		{
		printf("Binding error");
		close(sockfd);
		}
	
	actuallen=sizeof(clientaddr);
	recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr, &actuallen);

	strcpy(db[0].name,"www.google.com");
	strcpy(db[0].IP,"143.143.143.1");
	strcpy(db[1].name,"www.yahoo.com");
	strcpy(db[1].IP,"169.169.169.1");
	strcpy(db[2].name,"www.facebook.com");
	strcpy(db[2].IP,"111.111.111.1");


	for(i=0;i<3;i++)
	{
	if(strcmp(buff,db[i].name)==0)
		{
		flag=1;
		sentbytes=sendto(sockfd,db[i].IP,sizeof(db[i].IP),0,(struct sockaddr*)&clientaddr, sizeof(clientaddr));

		}
	}
	
	
	if(flag==0)
	{
		
		int sockfd2,retval2;
		int recedbytes2,sentbytes2;
		struct sockaddr_in serveraddr2;
		socklen_t len2;
		char buff2[MAXSIZE];
		sockfd2=socket(AF_INET,SOCK_DGRAM,0);
		if(sockfd2==-1)
		{
		printf("\nSocket Creation Error");

		}
		printf("%i",sockfd);
		serveraddr2.sin_family=AF_INET;
		serveraddr2.sin_port=htons(3389);
		serveraddr2.sin_addr.s_addr=inet_addr("127.0.0.1");
		len2=sizeof(serveraddr2);
		sentbytes2=sendto(sockfd2,buff,sizeof(buff),0,(struct sockaddr*)&serveraddr2,sizeof(serveraddr2));
		recedbytes2=recvfrom(sockfd2,buff2,sizeof(buff2),0,(struct sockaddr*)&serveraddr2,&len2);
		sentbytes=sendto(sockfd,buff2,sizeof(buff2),0,(struct sockaddr*)&clientaddr, sizeof(clientaddr));
		
		
		if(sentbytes2==-1)
			{
			printf("!!");
			close(sockfd2);
			}
		if(sentbytes==-1)
			{
			printf("!!");
			close(sockfd);
			}
		close(sockfd2);
		
	}
	close(sockfd);
}
