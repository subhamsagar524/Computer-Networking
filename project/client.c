/*  Client Code

	C program to connect with the server 
	and receive the result.

	Sample Output:

		On client1:
			Result: 100 300 500 700 900 

		On client2:
			Result: 200 400 600 800 1000 

*/

// Import Headers
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Driver Code
int main()
{
	// Enter name of the client
	char c_name[50];
	printf("\nEnter name of client: ");
	scanf("%[^\n]%*c", c_name);  

	// Creating and connecting client to server
	struct sockaddr_in ServerIp;
	printf("\nConnecting to server...");

	int sock = socket( AF_INET, SOCK_STREAM,0);

    ServerIp.sin_port = htons(1234);
    ServerIp.sin_family= AF_INET;
    ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");

    if( (connect( sock ,(struct sockaddr *)&ServerIp,sizeof(ServerIp))) == -1 )
        printf("\n Connection to socket failed \n");
    printf("\nConnected\n\nResult: ");

    // Making client waiting for the required data
    char msg[1000];
    int len = recv(sock,msg,500,0);
    msg[len] = '\0';

    // Printing the data
    fputs(msg,stdout);

    printf("\n");

	return 0;
}
