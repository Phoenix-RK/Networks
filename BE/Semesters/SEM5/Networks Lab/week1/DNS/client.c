#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>




#define PORT 1024
#define PORT1 2024
#define PORT2 3024
int main()
{

// ROOT

 
int i,sockid;
sockid=socket(AF_INET,SOCK_DGRAM,0);////////////////////////////////////////////////
if(sockid==-1)
{
printf("Socket Error");
return 0;
}
int recvbytes,sentbytes;
struct sockaddr_in client,client1,client2;
client.sin_family=AF_INET;
client.sin_port=htons(PORT);
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client.sin_zero[i]='\0';//////////////////////////////////
printf("\nConnected to Origin\n");
char hostname[100],ip[100],ip1[100],ip2[100];
printf("\nEnter HostName : ");
scanf(" %s",hostname);
int size=sizeof(struct sockaddr);
sentbytes=sendto(sockid,hostname,strlen(hostname),0,(struct sockaddr*)&client,size);
recvbytes=recvfrom(sockid,ip,sizeof(ip),0,NULL,NULL);
ip[recvbytes]='\0';
printf("\nIp from originserver is %s\n",ip);
close(sockid);

//TLD


int sockid1;
sockid1=socket(AF_INET,SOCK_DGRAM,0);
client1.sin_family=AF_INET;
client1.sin_port=htons(PORT1);
client1.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client1.sin_zero[i]='\0';
printf("\nConnected to Top level domain\n");
sentbytes=sendto(sockid1,hostname,strlen(hostname),0,(struct sockaddr*)&client1,size);
recvbytes=recvfrom(sockid1,ip1,sizeof(ip1),0,NULL,NULL);
ip1[recvbytes]='\0';
printf("\nIp from TLD is %s\n",ip1);
close(sockid1);


// Authoritative


int sockid2;
sockid2=socket(AF_INET,SOCK_DGRAM,0);
client2.sin_family=AF_INET;
client2.sin_port=htons(PORT2);
client2.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client2.sin_zero[i]='\0';
printf("\nConnected to Authoritative\n");
sentbytes=sendto(sockid2,hostname,strlen(hostname),0,(struct sockaddr*)&client2,size);
recvbytes=recvfrom(sockid2,ip2,sizeof(ip2),0,NULL,NULL);
ip2[recvbytes]='\0';
printf("\nIp from Authoritative is %s\n",ip2);
close(sockid2);

return 0;
}
