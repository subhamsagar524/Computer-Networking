#include <time.h>
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
	time_t t;
	int listenfd,connfd,len,n;
	char buff[200];

	struct sockaddr_in servaddr,cliaddr;
	len=sizeof(servaddr);
	servaddr.sin_family=AF_INET;

	servaddr.sin_addr.s_addr=htons( INADDR_ANY);

	servaddr.sin_port=htons(0);
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	bind(listenfd, (struct sockaddr *)&servaddr,len);
	getsockname(listenfd,(struct sockaddr *)&servaddr ,&len);
	printf("Port for client: %ld\n",(long)ntohs(servaddr.sin_port));
	
	printf("\nEnter Ctrl+C to terminate the chat...\n");
	do
	{
		listen(listenfd,5);
		connfd=accept(listenfd,(struct sockaddr *)&cliaddr ,&len);
		n=read(connfd , buff ,sizeof(buff));

		buff[n]=0;

		time(&t);
		printf("\n%sClient: %s\n" , ctime(&t), buff);
		
		//Server writes
		printf("\nYou: ");
		scanf("%s" , buff);
		write(connfd, buff ,sizeof(buff));

	}while(1);

	return 0;
}