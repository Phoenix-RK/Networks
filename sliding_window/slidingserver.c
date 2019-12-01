#include<netdb.h>
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include<stdio.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include<arpa/inet.h>
#include<unistd.h>

#define MAX 10
#define PORT 8501
#define SA struct sockaddr 

void chatting(int sockfd)
{
	char buff[MAX];
	int rws=10,flag=0;
	int n=0,i=0;
	for(;rws>0; )
	{
		printf("\nReceiver window size : %d\n",rws);

		//bzero(buff, MAX);
		
		read(sockfd, &buff[n++], sizeof(buff[0]));
		
		printf("Current receiver window size :%d\n",rws--);
		printf("last byte received :%c\n",buff[n-1]);
		printf("Position of Next expected byte :%d\n",n);
		flag=1;
		write(sockfd, &flag,sizeof(flag));
		//bzero(buff, MAX);		
		//n=0;
		printf("Current receiver buffer\n");
		for(i=0;i<n;i++)
		printf("%c\t",buff[i]);
		//write(sockfd, buff, sizeof(buff));
		/*if (strncmp("done",buff, 4)==0){
			printf("Server says byeeee\n");
			break;
		}*/

	}
}
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
		printf("Socket successfully binedd..\n"); 
	if ((listen(sockfd,5))!=0){
		printf("Listen failed\n");
		exit(0);
	}
	printf("Successful listen call\n");
	len = sizeof(cli);

	connfd = accept(sockfd, (SA*) &cli, &len);
	if (connfd < 0 )
	{
		printf("Server accept failed\n");
		exit(0);
	}
	printf("Server accepted the client\n");
	chatting(connfd);
	close(sockfd);
}

