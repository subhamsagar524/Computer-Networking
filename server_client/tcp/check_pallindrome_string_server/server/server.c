#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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
	n=read(connfd , buff ,sizeof(buff));

	buff[n]=0;
	buff[strlen(buff)-1] = '\0';

	int temp = checkPallindrome(buff);
	char res[1024];
	if(temp)
		strcpy(res, "String is pallindrome.");
	else
		strcpy(res, "String is not pallindrome.");

	write(connfd, res, sizeof(res));
	return 0;

}
