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
	int sockfd, retval; int arr[50], n,i;
	int sentbytes, rcvbytes;
	struct sockaddr_in serveraddr;
	char buffer[100], key[1]; socklen_t actlen;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		printf("\nSocket nahi bana.");
	}
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(3388);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	printf("Enter the number of elements. \n");
	scanf("%d", &n);
	printf("Enter the array. \n");
	for(i=0;i<n;i++)
	{
		scanf("%d", &arr[i]);
	}
	int sn = htonl(n);
	sentbytes = sendto(sockfd, &sn, sizeof(sn), 0, (struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(sentbytes == -1)
	{
		printf("\nOops.");
		close(sockfd);
	}
	sentbytes = sendto(sockfd, arr, sizeof(arr), 0, (struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(sentbytes == -1)
	{
		printf("\nOops.");
		close(sockfd);
	} int item, sitem;
	printf("Enter the element to search. \n");
	scanf("%d", &item);
	sitem = htonl(item);
	sentbytes = sendto(sockfd, &sitem, sizeof(sitem), 0, (struct sockaddr*)&serveraddr,sizeof(serveraddr));
	if(sentbytes == -1)
	{
		printf("\nOops.");
		close(sockfd);
	}
	
	rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr,&actlen);
	puts(buffer);
	printf("\n");
		
	close(sockfd);
}
