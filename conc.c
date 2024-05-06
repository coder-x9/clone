#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<time.h>
#include<errno.h>
int main(int argc,char*argv[])
{
int s,t,n;
struct sockaddr_in servaddr,local,rem;
char buffer[1024];
if(argc<3)
{
printf("\nusage:client<server_addr><port>");
exit(0);
}
if((s=socket(AF_INET,SOCK_DGRAM,0))<0)
{
perror("errror in socket creation");
exit(0);
}
bzero((char*)&local,sizeof(local));
local.sin_family=AF_INET;
local.sin_port=htons(6677);
local.sin_addr.s_addr=inet_addr(argv[1]);
if(bind(s,(struct sockaddr*)&local,sizeof(local))==-1)
{
perror("bind error");
exit(1);
}
bzero((char*)&servaddr,sizeof(local));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons((short)atoi(argv[2]));
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
strcpy(buffer,"TIME");
if(sendto(s,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
{
perror("error in sendto");
exit(0);
}
t=sizeof(servaddr);
printf("the current time is");
if((n=recvfrom(s,buffer,1024,0,(struct sockaddr*)&servaddr,&t))>0)
{
buffer[n]='\0';
fputs(buffer,stdout);
}
else
{
if(n<0)
{
perror("error in read form");
exit(0);
}
else
printf("server closed connection\n");
exit(1);
}
memset(buffer,0,100);
close(s);
return 0;
}
