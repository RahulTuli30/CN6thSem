#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

main()
{
int sockfd,retval;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr;
socklen_t len;
char buff[MAXSIZE];
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1)
{
printf("\nSocket Creation Error");

}
printf("%i",sockfd);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

printf("Enter the text\n");

scanf("%s",buff);


sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

if(sentbytes==-1)
{
printf("!!");
close(sockfd);
}
len = sizeof(serveraddr);
recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&serveraddr,&len);
puts(buff);
printf("\n");
close(sockfd);
}
