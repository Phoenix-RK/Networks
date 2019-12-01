
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<sys/types.h>
#include<netinet/in.h>
#include <netdb.h> 
#include<arpa/inet.h>
#include<unistd.h>
#define MAX 80 
#define PORT 8501
#define SA struct sockaddr 
void func(int sockfd) 
{ 
	char buff[10];
	int sws=10;
	int n,i,flag=0; 
	for (;;) { 
	printf("Sender window size :10\n");
		bzero(buff, sizeof(buff)); 
		printf("Enter the string : \n"); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') 
			;
buff[n-1]='\0';
		sws=sws-strlen(buff);
		printf("Sender window size :%d\n",sws);
		printf("last byte written :%c\n",buff[strlen(buff)-1]);
		for(i=0;i<strlen(buff);i++)
		{ 
		printf("Last byte sent :%c\n",buff[i]);
		
		write(sockfd, &buff[i], sizeof(buff[i])); 
		while(flag==0)
		read(sockfd,&flag,sizeof(flag));
		printf("Last byte acknowledged :%c\n",buff[i]);
		printf("Current server window size :%d\n",sws++);
		
		
		} 
	} 
} 

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket created..\n"); 
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect (sockfd, (SA*)&servaddr, sizeof(servaddr)) !=0)
	{
		printf("Can't connect to server..failed\n");
		exit(0);
	}
	else
	{
		char buffer[250];
		printf ("Connected to server\n");
		/*while(1)
		{
		printf("Enter data\n");
		scanf("%s",buffer);
		if(strlen(buffer)>5)
		{
		}
		}*/
		func(sockfd);
		close(sockfd);
	}
}
