#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
char buff[MAX];
int n;
for (;;){
bzero(buff,sizeof(buff));
printf("Enter the string:");
n = 0;
while((buff[n++] = getchar()) != '\n');
write(sockfd, buff, sizeof(buff));
bzero(buff, sizeof(buff));
read(sockfd,buff,sizeof(buff));
printf("From server: %s", buff);
if ((strncmp(buff, "exit",4)) == 0){
	printf("Client Exit...\n");
	break;
}
}
}

int main()
{
int sockfd=socket(AF_INET,SOCK_STREAM,0);

struct sockaddr_in cliaddr;
cliaddr.sin_family = AF_INET;
cliaddr.sin_port = htons(9111);
cliaddr.sin_addr.s_addr= inet_addr("127.0.0.1");

int connfd = connect(sockfd, (SA*)&cliaddr, sizeof(cliaddr));

if (connfd == -1)
{
	printf("Connection not established\n");
}
else
{
	printf("Connected to server\n");
	func(sockfd);
	close(sockfd);
}
}


