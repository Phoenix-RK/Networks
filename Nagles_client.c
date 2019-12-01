#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 80 
#define PORT 8022
#define SA struct sockaddr 
void func(int sockfd) 
{ 
	char buff[MAX], f[MAX]; 
	int len,nframes,flag; 
	int i,j,k;//looping
	float rtt,utt,totaltime;
	for(;;)
	{
		printf("Enter RTT, UTT\n");
		//	scanf("%d%d%d",&rtt,&utt,&nframes);
		scanf("%f",&rtt);
		scanf("%f",&utt);
		send(sockfd,&rtt,sizeof(rtt),0);		
		printf("Enter data\n");
		scanf("%s",f);
		nframes= strlen(f);
		printf("Total no of frames : %d\n",nframes);
		flag=0;
		bzero(buff, sizeof(buff)); 
		buff[0]=f[0];
		write(sockfd,&buff[0],sizeof(buff[0]));
		printf("Sent first frame :%c\n",buff[0]);
		read(sockfd,&flag,sizeof(flag));
		printf("First frame got ack : %d\n",flag);
		len =1;
		//printf("%f",rtt/utt);
		while(len < nframes)
		{
			//	flag=0;
			for(i=0;i<(int)(rtt/utt);i++)
				buff[i]=f[len++];
			
			while(flag==0)
				read(sockfd,flag,sizeof(flag)); //waitfor acknowledgement
			totaltime+=rtt;
			write(sockfd, &buff,sizeof(buff)); //send next packet
			printf("At time=%f Grouped and sent  as :%s \n",totaltime,buff);
			//printf("%s",buff);


		}
		if ((strncmp(buff, "done", 4)) == 0) { 
			printf("Client says byeeee...\n"); 
			break; 
		}
	}
}
/*	while ((buff[n++] = getchar()) != '\n') 
	; 
	write(sockfd, buff, sizeof(buff)); 
	bzero(buff, sizeof(buff)); 
	read(sockfd, buff, sizeof(buff)); 
	printf("From Server : %s", buff); */

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 
	int delay;

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket created..\n");
	int flag=1;
	/*if (setsockopt(sockfd, 1, 1, (void *) &flag, sizeof(flag)))
	  {
	  perror("Error :");
	  exit(0);
	  }
	  printf("Delay :\n");
	  scanf("%d",&delay);
	 */
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
		func(sockfd);
		close(sockfd);
	}
	return 0;
}
/*while(1)
  {
  i=0;
  printf("\nEnter a string :\t");
  scanf("%s",buffer);
  if(strlen(buffer)<5)
  {
  int x=strlen(buffer);
  int flag;
  char y[10];
  printf("Size less than packet size\n");
  printf("Acknowledge? enter 1 or 0\n");
  scanf("%d",&flag);
  if(flag == 1)
  {
  printf("the text is %s\n",buffer);
  send(sockfd, buffer, strlen(buffer), 0);
  printf("Finished\n");
  }
  else if (flag == 0)
  {
  printf("Enter further \n");
  scanf("%s",y);
  strcat(buffer,y);
  send(sockfd, buffer, strlen(buffer), 0);

  }
  }
  else

  {

  send(sockfd, buffer, strlen(buffer), 0);
  }
//func(sockfd);

read(sockfd, buffer, sizeof(buffer)); 
printf("From Server : %s", buffer); 
}
close(sockfd);
}
return 0;
}*/
