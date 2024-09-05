//UDP Client program
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("172.16.57.142");//**
	address.sin_port=htons(9704);
	char buf[25],buf1[25];
	printf("enter buf\n");
	gets(buf);
	int len=sizeof(address);
	int m=sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&address, len);
	int n=recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr*)&address, &len);
	printf("the server echo is\n");
	puts(buf);
	printf("matrix code\n");
	int rows=0, cols=0;
	printf("enter number of rows\n");
	scanf("%d",&rows);
	printf("enter number of columns\n");
	scanf("%d",&cols);
	char row_col[3];
	row_col[0]=rows;
	row_col[1]=cols;
	row_col[2]='\n';
	int q=sendto(sd,row_col,sizeof(row_col),0,(struct sockaddr *)&address, len);
	char arr[cols];
	for(int i=0;i<rows;i++)
	{
		printf("Row %d\n",i+1);
		for(int j=0;j<cols;j++)
		{
			scanf("%c",arr[j]);
		}
		arr[cols]='\n';
		int r=sendto(sd, arr, sizeof(arr), 0, (struct sockaddr *)&address, len);
	}
	return 0;
}
