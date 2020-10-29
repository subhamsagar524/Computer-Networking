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
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	connect(sockfd,(struct sockaddr *)&cliaddr,len);

	// Input and send the number to server
	printf("\nEnter a number: ");
	scanf("%s", buff);
	write(sockfd, buff ,sizeof(buff));

	// Read values of multiplied by 2 and squares from server
	n=read(sockfd,buff ,sizeof(buff));
	buff[n]=0;
	printf("\nReceived 2n and n^2 from server: %s\n", buff);

	// Get the sum of received values
	char* temp;
	int sum = 0;
	temp = strtok(buff, " ");
	while( temp != NULL )
	{
      sum += atoi(temp);
      temp = strtok(NULL, " ");
   	}

   	// Send the sum to the server
   	strcpy(buff, "");
	sprintf (buff, "%d", sum);
	write(sockfd, buff ,sizeof(buff));

	return 0;
}
