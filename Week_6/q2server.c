//TCP Server Program
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<ctype.h>
#define PORTNO 10200

void toggle(char *str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		if(islower(str[i]))
			str[i]=toupper(str[i]);
		else if(isupper(str[i]))
			str[i]=tolower(str[i]);
	}
}
int main()
{
	int sockfd,newsockfd,portno,clilen,n=1;char buf[256];
	struct sockaddr_in seraddr,cliaddr;
	int i,value;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = inet_addr("172.16.57.142");
	seraddr.sin_port = htons(PORTNO);	
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
	// Create a connection queue, ignore child exit details, and wait for clients
	listen(sockfd,5);
	while(1)
	{
		//Accept the connection
		clilen = sizeof(clilen);
		newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		//Fork to create a process for this client and perform a test to see whether
		//you’re the parent or the child:
		if(fork()==0)
		{
		// If you’re the child, you can now read/write to the client on newsockfd.
			n = read(newsockfd,buf,sizeof(buf));
			printf(" \nMessage from Client %s \n",buf);
			toggle(buf);
			n = write(newsockfd,buf,sizeof(buf));
			close(newsockfd);
			exit(0);
		}
	//Otherwise, you must be the parent and your work for this client is 	finished
		else
			close(newsockfd);
	}
}
