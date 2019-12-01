/*#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#define MAX 80
#define PORT 9999
#define SA struct sockaddr
void func(int sockfd)
{
	char buff[MAX];
	int n;
	for(;;)
	{
		bzero(buff,sizeof(buff));
		printf("\nEnter the string:");
		n=0;
		while((buff[n++]=getchar())!='\n')
			;

		write(sockfd,buff,sizeof(buff));
		bzero(buff,sizeof(buff));
		read(sockfd,buff,sizeof(buff));
		printf("\nFrom Server: %s",buff);
		if(strncmp(buff,"exit",4)==0)
		{
			printf("\nClient Exit\n");
			break;
		}
	}
}


int main()
{
	int sockfd,connfd;
	struct sockaddr_in servaddr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
	printf("\nSocket creation failed\n");
	exit(0);
	}

	else
	printf("\nSocket Successfully created\n");

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0)
	{
	printf("\nConnection with the server failed\n");
	exit(0);
	}
	else
	printf("\nConnected to the server\n");

	func(sockfd);
	close(sockfd);


	}*/
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<time.h>
#define MAX 300
#define SA struct sockaddr
#define PORT 8001

void func(int sockfd)
{
	time_t t;
	char buf[MAX],result[MAX];
	int n=0,x;
	for(;;)
	{
		bzero(buf,MAX);
		n=0;
		while((buf[n++]=getchar())!='\n')
			;
		write(sockfd,buf,sizeof(buf));
		bzero(buf,sizeof(buf));
		x=read(sockfd,result,sizeof(result));
		result[x]='\0';
		printf("\nFrom server:%s",result);
		//printf(ctime(&t));
	/*	if(strncmp(buf,"exit",4)==0)
		{
			break;
		}
*/
	}

}


int main()
{
	int sockfd;
	struct sockaddr_in servaddr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		printf("\nSocket creation failed");
		exit(0);
	}
		
	else
	printf("\nsocket creation success");
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);

	if(connect(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0)
	{
		printf("\nConnection failed");
		exit(0);
	}
	else
		printf("\nconnection success");

	func(sockfd);
	close(sockfd);

}

