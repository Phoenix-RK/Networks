#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#define MAX 100
int *func(int *a,int *b,int *carry)
{
 int *ab;
 ab=(int*)malloc(sizeof(int)*16);
int i;
 for(i=15;i>=0;i--)
 {
  if(a[i]==0&&b[i]==0&&*carry==0)
{
 ab=(int*)malloc(sizeof(int)*16);
 int i;
for(i=15;i>=0;i--)
{
if(a[i]==0&&b[i]==0&&*carry==0)
{
 ab[i]=0;
*carry=0;
}
else if(a[i]==0 && b[i]==0 && *carry==1)
{
 ab[i]=1;
*carry=0;
}
else if(a[i]==0 && b[i]==1 && *carry==0)
{
 ab[i]=1;
*carry=0;
}
else if(a[i]==0 && b[i]==1 && *carry==1)
{
 ab[i]=0;
*carry=1;
}
else if(a[i]==1 && b[i]==0 && *carry==0)
{
 ab[i]=1;
*carry=0;
}
else if(a[i]==1 && b[i]==0 && *carry==1)
{
 ab[i]=0;
*carry=1;
}
else if(a[i]==1 && b[i]==1 && *carry==0)
{
 ab[i]=0;
*carry=1;
}
else if(a[i]==1 && b[i]==1 && *carry==1)
{
 ab[i]=1;
*carry=1;
}
else
 break;
}
}
}
return ab;
}
int main()
{
  struct sockaddr_in ser, cli; 
  
    // socket create and varification 
    int sockid = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockid == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&ser, sizeof(ser)); 
  
    // assign IP, PORT 
    ser.sin_family = AF_INET; 
    ser.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    ser.sin_port = htons(3555); 
  
    // connect the client socket to server socket 
    if (connect(sockid, (struct sockaddr*)&ser, sizeof(ser)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  int a[16],b[16],c[16],d[16],check[16],*carry,i,com[16],flag=0;
int len = sizeof(cli); 
int new_sock=accept(sockid,(struct sockaddr*)&cli,&len);
carry=(int*)malloc(sizeof(int)*1);
*carry=0;
for(i=0;i<16;i++)
 scanf("%d",&a[i]);
for(i=0;i<16;i++)
 scanf("%d",&b[i]);
for(i=0;i<16;i++)
 scanf("%d",&c[i]);
for(i=0;i<16;i++)
 scanf("%d",&d[i]);
int *ab=func(a,b,carry);
printf("\n bits of ab");
for(i=0;i<16;i++)
printf("%d",ab[i]);
int *cd=func(c,d,carry);
printf("\n bits of cd");
for(i=0;i<16;i++)
printf("%d",cd[i]);
int *abcd=func(ab,cd,carry);
printf("\n bits of abcd");
for(i=0;i<16;i++)
printf("%d",abcd[i]);
for(i=0;i<16;i++)
{
if(abcd[i]==0)
check[i]=1;
else
check[i]=0;
}
printf("Checksum is");
for(i=0;i<16;i++)
printf("%d",check[i]);
char str[100];
write(sockid,a,sizeof(a));
read(sockid,str,sizeof(str));
write(sockid,b,sizeof(b));
read(sockid,str,sizeof(str));
write(sockid,c,sizeof(c));
read(sockid,str,sizeof(str));
write(sockid,d,sizeof(d));
read(sockid,str,sizeof(str));
write(sockid,check,sizeof(check));
read(sockid,str,sizeof(str));
}


