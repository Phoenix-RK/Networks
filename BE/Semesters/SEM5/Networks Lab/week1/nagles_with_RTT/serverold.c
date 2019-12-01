#include<netdb.h>
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include<stdio.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8012
#define SA struct sockaddr 

void chatting(int sockfd)
{
	char buff[MAX];
	int n;
	for(;;)
	{
	bzero(buff, MAX);
	read(sockfd, buff, sizeof(buff));
	printf("From client : %s\n",buff);

	bzero(buff, MAX);	
	strcpy(buff,"received");
	write(sockfd, buff, sizeof(buff));
	printf("Sleeping for a while\n");
	sleep(5);
	}
	//while((buff[n++] = getchar())!='\n');
	//printf("%s\n",buff);
	//write(sockfd, buff, sizeof(buff));
	//if (strncmp("done",buff, 4)==0){
	//	printf("Server says byeeee\n");
	//	break;
	//}

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

