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
	
	//while(1)
	{
		rcvbytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &actlen);
		if(rcvbytes == -1)
		{
			close(sockfd);
		}
		//if(strcmp(buffer, "stop")==0)
		//	break;
		printf("%s",buffer);
		printf("\n");

		char words[50][50];
	    int i=0, j=0, k;
	    for(k=0;buffer[k]!='\0';k++)
	    {
	        if(buffer[k] == ' ')
	        {
	            words[i][j] = '\0';
	            i++;
	            j=0;
	        }
	        else
	        {
	            words[i][j] = buffer[k];
	            j++;
	        }
	    }
	    words[i][j] = '\0';
	    int count = i+1;

	    rcvbytes = recvfrom(sockfd, find, sizeof(find), 0, (struct sockaddr*)&clientaddr, &actlen);
		if(rcvbytes == -1)
		{
			close(sockfd);
		}
		rcvbytes = recvfrom(sockfd, rep, sizeof(rep), 0, (struct sockaddr*)&clientaddr, &actlen);
		if(rcvbytes == -1)
		{
			close(sockfd);
		}
		i = 0;
	    while(i<count)
	    {
	        if(strcmp(words[i], find) == 0)
	        {
	            strcpy(words[i], rep);
	            break;
	        }
	        else
	        {
	            i++;
	        }
	    }
	    i=1,j=0;
	    strcpy(buffer,words[0]);
	    while(i<count)
	    {
	        strcat(buffer, " ");
	        strcat(buffer, words[i]);
	        i++;
	    }
	    
		sentbytes = sendto(sockfd, buffer, sizeof(buffer),0,(struct sockaddr*)&clientaddr, sizeof(clientaddr));
		if(sentbytes == -1)
		{
			close(sockfd);
		}
	}
	close(sockfd);
}
