//TCP Client program
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("172.16.57.142");
	address.sin_port=htons(10200);
	int len=sizeof(address);
	int result=connect(sd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
		perror("\nCLIENT ERROR");
		exit(1);
	}
	char buf[25],buf1[25];
	printf("enter buf\n");
	scanf("%s",buf);
	buf[strlen(buf)]='\0';
	write(sd,buf,sizeof(buf));
	int n=read(sd,buf,sizeof(buf));
	printf("the toggled string by server is\n");
	puts(buf);
	return 0;
}
