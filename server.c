/*#include<netdb.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#define MAX 80
#define PORT 9999
#define SA struct sockaddr
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	for (;;) { 
		bzero(buff, MAX); 
		read(sockfd, buff, sizeof(buff));  
		printf("From client: %s\n To client : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') ; 

		write(sockfd, buff, sizeof(buff)); 

		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

int main()
{
	int sockfd,connfd,len,i;
	struct sockaddr_in servaddr,cli;
	time_t t;	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1 ) 
		printf("\nsocket created");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");;
	servaddr.sin_port =htons(PORT);

	if(bind(sockfd,(SA*)&servaddr,sizeof(servaddr))==0)
		printf("\nserver is binded");
	if(listen(sockfd,5)==0)
		printf("\nserver is listening...");

	len=sizeof(cli);
	connfd=accept(sockfd,(SA*)&cli,&len);
	printf(c_time(&t));
	func(connfd);
	close(sockfd);
	}
	*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>//**
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<time.h>
#include<fcntl.h>
#define PORT 8001
#define MAX 300
#define SA struct sockaddr
void func(int sockfd)
{

	char buf[MAX],result[MAX];
	int n=0,len,fd;
	for(;;)
	{
		bzero(buf,MAX);
		len=read(sockfd,buf,sizeof(buf));
		buf[len]='\0';
		fd=open("text.txt",O_RDWR|S_IWRITE|S_IREAD);
		if(fd==-1)
			printf("\nError");
		else
		{
			printf("\nFrom client:%s",buf);
			bzero(result,MAX);
			lseek(fd,0,0);
			read(fd,result,300);

//		while((buf[n++]=getchar())!='\n')
//			;
			write(sockfd,result,sizeof(result));/*

		if(strncmp(buf,"exit",4)==0)
		{
			break;#include<sys/stat.h>
		}*/
		}
		
	}

}


int main()
{
	int sockfd,confd;
	time_t t;
	struct sockaddr_in servaddr,cli;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		printf("\nsocket creation failed");

	}
	else
	{
		printf("\nSocket creation success");

	}

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(PORT);

	if(bind(sockfd,(SA*)&servaddr,sizeof(servaddr))!=0)
		printf("\nBind failed");

	else{
		printf("\nBind success");
	}
	if(listen(sockfd,5)==0)
		printf("\nserver listening");
	int len=sizeof(cli);
	printf("%s",asctime(localtime(&t)));
	confd=accept(sockfd,(SA*)&cli,&len);
	func(confd);
	close(sockfd);
	return 0;
}

