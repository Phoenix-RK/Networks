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
	void main()
	{

		struct sockaddr_in ser, cli; 

		// socket create and verification 
		int sockid=socket(AF_INET,SOCK_STREAM,0);
		if(sockid==-1)
			printf("\nFailed");
		else
			printf("\nSocket created successfully");
		ser.sin_family=AF_INET;
		ser.sin_port=htons(3555);
		ser.sin_addr.s_addr=htonl(INADDR_ANY);
		if(bind(sockid,(struct sockaddr*)&ser,sizeof(ser))!=0)
			printf("\nBind Failed");
		else
			printf("\nBind success");
		if(listen(sockid,10)!=0)
			printf("\nListen failed");
		else
			printf("\nListen success");
		int len=sizeof(cli);
		int new_sock=accept(sockid,(struct sockaddr*)&cli,&len);
		int a[16],b[16],c[16],d[16],check[16],*carry,i,com[16],flag=0;
		carry=(int*)malloc(sizeof(int));
		*carry=0;
		char str[]="ack";
		read(new_sock,a,sizeof(a));
		write(new_sock,str,sizeof(str));
		read(new_sock,b,sizeof(b));
		write(new_sock,str,sizeof(str));
		read(new_sock,c,sizeof(c));
		write(new_sock,str,sizeof(str));
		read(new_sock,d,sizeof(d));
		write(new_sock,str,sizeof(str));
		read(new_sock,check,sizeof(check));
		write(new_sock,str,sizeof(str));
		printf("Value of:\n");
		printf("\na - \t");
		for(i=0;i<16;i++)
			printf("%d",a[i]);
		printf("Value of:\n");
		printf("\nb - \t");
		for(i=0;i<16;i++)
			printf("%d",b[i]);
		printf("Value of:\n");
		printf("\nc - \t");
		for(i=0;i<16;i++)
			printf("%d",c[i]);
		printf("Value of:\n");
		printf("\nd - \t");
		for(i=0;i<16;i++)
			printf("%d",d[i]);

		int *ab=func(a,b,carry);
		printf("\n bits of ab");
		for(i=0;i<16;i++)
			printf("%d",ab[i]);
		int *cd=func(c,d,carry);
		printf("\n bits of cd");
		for(i=0;i<16;i++)
			printf("%d",cd[i]);
*carry=0;
		int *abcd=func(ab,cd,carry);
		printf("\n bits of abcd");
		for(i=0;i<16;i++)
			printf("%d",abcd[i]);
*carry=0;
		int *sum=func(abcd,check,carry);
		printf("\n bits of sum");
		for(i=0;i<16;i++)
			printf("%d",sum[i]);
		for(i=0;i<16;i++)
		{
			if(sum[i]==0)
				com[i]=1;
			else
				com[i]=0;
		}

		printf("\nBITS OF COMPLEMENT..\n");
		for(i=0;i<16;i++)
			printf("%d",sum[i]);

		for(i=0;i<16;i++)
		{
			if(sum[i]==0)
				continue;
			else
				flag++;
		}
		if(flag==0)
			printf("\nData is accepted");
		else
			printf("\nData not Accepted\n");
	}








