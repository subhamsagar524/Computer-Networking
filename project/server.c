/*  Server Code

    C program to accept 10 tuples,
    If first number is 1: then 2nd number is sent to 1st client
    If second number is 2: then 2nd number is sent to 2nd client

    Sample Input: 1 100                                  
				  2 200
				  1 300
				  2 400
				  1 500
				  2 600
				  1 700
				  2 800
				  1 900
				  2 1000

*/

// Import Headers
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

// This keeps track of both the clients
int clients[2];

// Driver Function
int main()
{
    // Max clients connections needed are two
	int clients[2];

	// Input initial data[10 tuples]
	printf("Enter 10 tuples(x, y): \n");
	int x[10], y[10];
	for ( int i = 0; i < 10; i++ )
		scanf("%d%d", &x[i], &y[i]);

	// Creating the server
	struct sockaddr_in ServerIp, ClientIp;
	int len = sizeof(ServerIp);
	int sock=0 , Client_sock=0;
	ServerIp.sin_family = AF_INET;
    ServerIp.sin_port = htons(1234);
    ServerIp.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Initialise socket
    sock = socket( AF_INET , SOCK_STREAM, 0 );
    printf("\nCreating Socket...\nBinding...\n");
    
    // Binding socket
    bind( sock, (struct sockaddr *)&ServerIp, sizeof(ServerIp));
    printf("Server Started\n\n");

    // Let the server listen for 2 clients
    listen( sock ,2 );
    printf("Waiting for two client to connect...\n");

    Client_sock = accept(sock, (struct sockaddr *)&ClientIp, &len);
    clients[0]= Client_sock;
    printf("\nFirst Client Connected");

    Client_sock = accept(sock, (struct sockaddr *)&ClientIp, &len);
    clients[1]= Client_sock;
    printf("\nSecond Client Connected");

    // Prepareing the data for both the clients
    // Enclosing results to send both the clients
    char msg1[1000] = "";
    char msg2[1000] = "";
    char temp[50];

    for (int i = 0; i < 10; i++)
    {
    	sprintf(temp, "%d", y[i]);

    	if (x[i] == 1)
    	{
    		strcat(msg1, temp);
    		strcat(msg1, " ");
    	}
    	else
    	{
    		strcat(msg2, temp);
    		strcat(msg2, " ");
    	}
    }

    // Sending data
    if(send(clients[0],msg1,strlen(msg1),0) < 0)
        printf("sending failure \n");
    printf("\n\nData sent to 1st client");

    if(send(clients[1],msg2,strlen(msg2),0) < 0)
        printf("sending failure \n");
    printf("\nData sent to 2nd client\n");

	return 0;
}
