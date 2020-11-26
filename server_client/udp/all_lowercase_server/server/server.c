#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024
int main(int argc,char **argv)
{
	int sockfd;
	int n;
	socklen_t len;
	char msg[1024];
	struct sockaddr_in servaddr,cliaddr;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	//bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(5035);
	printf("\n\n Binded");
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	
	printf("\n\n Listening...");
	printf("\n ");
	len=sizeof(cliaddr);
	n=recvfrom(sockfd,msg,MAXLINE,0,(struct sockaddr*)&cliaddr,&len);
	
	printf("\n Received Client's String: %s\n",msg);

	// Converting to all lowercase
	for(int i = 0; i <= msg[i] != '\0'; i++)
		if(msg[i] >= 'A' && msg[i] <= 'Z')
			msg[i] = msg[i] + 32;

	printf("\n  Modifing and sending...\n\n");
	if(n<6)
	perror("send error");

	sendto(sockfd,msg,n,0,(struct sockaddr*)&cliaddr,len);
	
	return 0;
}
