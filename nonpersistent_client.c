#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include <netdb.h> 
#include<net/if_arp.h>
#include<time.h> 
#define MAX 80 
#define PORT 8955
#define SA struct sockaddr 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	
	bzero(buff, sizeof(buff)); 
	printf("Enter the string : "); 
	n = 0; 
	while ((buff[n++] = getchar()) != '\n') 
		; 
	if(strcmp(buff,"exit"))
	write(sockfd, buff, sizeof(buff)); 
	bzero(buff, sizeof(buff)); 
	read(sockfd, buff, sizeof(buff)); 
	printf("From Server : %s", buff); 
	
	printf("***Closed connection***\n"); 

} 


int main() 
{ 
	while(1)
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
			printf ("Connected to server\n");

			char buff[MAX]; 
			int n; 

			bzero(buff, sizeof(buff)); 
			printf("Enter the string : "); 
			n = 0; 
			while ((buff[n++] = getchar()) != '\n') 
				; 
			if(strcmp(buff,"exit"))
				write(sockfd, buff, sizeof(buff)); 
			bzero(buff, sizeof(buff)); 
			read(sockfd, buff, sizeof(buff)); 
			printf("From Server : %s", buff); 

			printf("***Closed connection***\n"); 

		} 


		close(sockfd);
	}
}

