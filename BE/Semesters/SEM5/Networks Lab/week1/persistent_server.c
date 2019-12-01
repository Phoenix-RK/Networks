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
#define port 3012
#define MAX 80
#define LEN 512
#define SA struct sockaddr
void func(int conid)
{
		char buff[MAX]; 
		int n; 
		for (;;) { 
		bzero(buff, MAX); 

		read(conid, buff, sizeof(buff)); 
		printf("From client: %s\t ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		write(conid, buff, sizeof(buff)); 

		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break;
		}
		}
	

}
int main()
{
	int sockid,conid,len,i;
	char buf;
	struct sockaddr_in servaddr,cli;
	sockid = socket(AF_INET,SOCK_STREAM,0);
	if(sockid == -1 ) 
		printf("socket created");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");;
	servaddr.sin_port =htons(port);
	if(bind(sockid,(SA*)&servaddr,sizeof(servaddr))==0)
		printf("server is binded");
	if(listen(sockid,5)==0)
		printf("server is listening...\n");
	len = sizeof(cli);
	conid = accept(sockid,(SA*)&cli,&len);
	while(1)
	{
		func(conid);
	}
	return 0;
}  

