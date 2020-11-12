#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	int sockfd,len,n;
	long port;
	char buff[200];
	struct sockaddr_in cliaddr;
	len=sizeof(cliaddr);

	printf("Enter the port number you got from Server side:");
	scanf("%ld" ,&port);

	cliaddr.sin_family=AF_INET;
	cliaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	cliaddr.sin_port=htons(port);

	printf("\nEnter Ctrl+C to terminate the chat...\n");
	do
	{
		sockfd=socket(AF_INET,SOCK_STREAM,0);
		connect(sockfd,(struct sockaddr *)&cliaddr,len);
		printf("\nYou: ");
		scanf("%s", buff);
		write(sockfd, buff ,sizeof(buff));
		n=read(sockfd,buff ,sizeof(buff));

		buff[n]=0;

		printf("\nServer: %s\n" , buff);

	}while(1);

	return 0;
}
