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

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd==-1)
	{
		printf("Failed to create socket\n");
		exit(0);
	}
	printf("Socket creation success\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =  htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket binding failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 
	if ((listen(sockfd,5))!=0){
		printf("Listen failed\n");
		exit(0);
	}
	printf("Successful listen call\n");
	len = sizeof(cli);
	while(1)
	{
	connfd = accept(sockfd, (SA*) &cli, &len);
	if (connfd < 0 )
	{
		printf("Server accept failed\n");
		exit(0);
	}
	printf("Server accepted the client\n");

	char buff[MAX];
	int n;

	bzero(buff, MAX);
	read(sockfd, buff, sizeof(buff));
	printf("From client : %s \t To client : ",buff);
	bzero(buff, MAX);		
	n=0;

	while((buff[n++] = getchar())!='\n');
	printf("%s\n",buff);
	write(sockfd, buff, sizeof(buff));
	if (strncmp("done",buff, 4)==0){
		printf("Server says bye\n");
		break;
	}
	close(sockfd);
	sleep(2.3);
	}
}

