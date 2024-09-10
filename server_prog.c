#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
char buff[MAX];
int n;
for(;;){
bzero(buff, MAX);
read(connfd, buff,sizeof(buff));
printf("From client: %s\t \n Confirm the message To client:", buff);
bzero(buff, MAX);
n = 0;
while ((buff[n++] = getchar()) != '\n');
write(connfd, buff, sizeof(buff));
if (strncmp("exit",buff,4) ==0){
	printf("Server Exit...\n");
	break;
}
}
}
int main()
{
int sockfd = socket(AF_INET, SOCK_STREAM,0);
struct sockaddr_in servaddr,cli;

servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(9111);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

bind(sockfd,(SA*)&servaddr, sizeof(servaddr));
listen(sockfd,5);
int len = sizeof(cli);
int connfd = accept(sockfd, (SA*)&cli, &len);

func(connfd);
close(connfd);

}
