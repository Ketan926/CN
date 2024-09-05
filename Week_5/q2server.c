#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
	int sd;
	char buf[25];
	struct sockaddr_in sadd,cadd;
	//Create a UDP socket
	sd=socket(AF_INET,SOCK_DGRAM,0);
	//Construct the address for use with sendto/recvfrom... */
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("172.16.57.142");//**
	sadd.sin_port=htons(9704);
	int result=bind(sd,(struct sockaddr *)&sadd,sizeof(sadd));
	int len=sizeof(cadd);
	int m=recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,&len);
	printf("the server send is\n");
	puts(buf);
	int n=sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,len);
	char row_col[3];
	m=recvfrom(sd,row_col,sizeof(row_col),0,(struct sockaddr *)&cadd,&len);
	printf("the server send is\n");
	puts(row_col);
	printf("number of rows is %c\n",row_col[0]);
	printf("number of columns is %c\n",row_col[1]);
	int rows=row_col[0];
	int cols=row_col[1];
	int matrix[rows][cols];
	for(int i=0;i<rows;i++)
	{
		m=recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,&len);
		for(int j=0;j<cols;j++)
		{
			matrix[i][j]=buf[j]-'0';
		}
	}
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
