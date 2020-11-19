#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#define MAXLINE 1024

int checkPallindrome(char* string) 
{ 
    char *ptr, *rev;
    ptr = string;

    while (*ptr != '\0') {
        ++ptr;
    }
    --ptr;

    for (rev = string; ptr >= rev;) {
        if (*ptr == *rev) {
            --ptr;
            rev++;
        }
        else
            break;
    }

    if (rev > ptr)
        return 1;
    else
        return 0; 
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
	printf("\n Checking for Pallindrome...");
	
	msg[strlen(msg)-1] = '\0';

	int temp = checkPallindrome(msg);
	char res[1024];
	if(temp)
		strcpy(res, "String is pallindrome.");
	else
		strcpy(res, "String is not pallindrome.");

	if(n<6)
	perror("send error");
	sendto(sockfd,res,n,0,(struct sockaddr*)&cliaddr,len);
	printf(" Sent\n\n");
	return 0;
}
