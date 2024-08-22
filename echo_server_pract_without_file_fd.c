#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>

int main()
{
int sockfd, connfd,n;
struct sockaddr_in servaddr,cliaddr;
char buff[1000];
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(5010);

sockfd =socket(AF_INET, SOCK_STREAM,0);
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

listen(sockfd,1);

for (;;)
{

connfd = accept(sockfd, (struct sockaddr*)&cliaddr,sizeof(cliaddr));

printf("\n Received request...\n");

while((n = recv(connfd, buff, 1000,0)) >0)
{
printf("Received n bytes of string from and resent to client:%d \n",n);
//FILE *file = fopen("message_history.txt","w");
puts(buff);
//fwrite(buff,1, n, file);
send(connfd,buff,n,0);
}

if(n<0)
{
perror("Read error");
exit(1);
}

close(connfd);
}
close(sockfd);
}









