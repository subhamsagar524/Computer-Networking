#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024

void strrev(char *s)
{
    int length, c;
    char *begin, *end, temp;
    length = strlen(s);
    begin = s;
    end = s;

    for(c = 0; c < length - 1; c++)
    	end++;
  
    for (c = 0; c < length/2; c++)
    {        
		temp   = *end;
		*end   = *begin;
		*begin = temp;
		begin++;
		end--;
    }
}

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
	
	printf("\n Client's Message : %s\n",msg);
	printf("\n Reversing the string...\n");
	strrev(msg);
	if(n<6)
	perror("send error");
	sendto(sockfd,msg,n,0,(struct sockaddr*)&cliaddr,len);
	printf(" Sent\n\n");
	return 0;
}
