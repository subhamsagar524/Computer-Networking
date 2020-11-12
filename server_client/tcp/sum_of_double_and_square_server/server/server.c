/* To implement the program where client reads a number x 
   and sends to server. The server sends 2x and x^2 to the 
   client. The client adds them and sends the result to the 
   server. Server displays them.
*/

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
	printf("Port for client=%ld\n",(long)ntohs(servaddr.sin_port));
	listen(listenfd,5);
	connfd=accept(listenfd,(struct sockaddr *)&cliaddr ,&len);
	
	// Read the number from client
	n=read(connfd , buff ,sizeof(buff));
	buff[n]=0;
	int num = atoi(buff);
	printf("\nReceived number from client= %d\n", num);

	// Store multiplied by 2 and squares in an string
	int numdata[2];
	numdata[0] = num * 2;
	numdata[1] = num * num;

	strcpy(buff, "");
	for(int i = 0; i < 2; i++)
	{
		char temp[50];
		sprintf (temp, "%d", numdata[i]);
		strcat(buff, temp);
		strcat(buff, " ");
	}

	// Send the two numbers to client
	write(connfd, buff ,sizeof(buff));

	// Receive the sum and print in server
	n=read(connfd , buff ,sizeof(buff));
	buff[n]=0;

	printf("\nReceived sum from client: %s\n", buff);

	return 0;
}
