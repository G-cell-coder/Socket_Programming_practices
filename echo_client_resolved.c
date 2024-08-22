#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdio.h>

int main()
{
int sockfd,connfd,n;
struct sockaddr_in cliaddr, servaddr;
char sendline[1000], recvline[1000];

cliaddr.sin_family = AF_INET;
cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
cliaddr.sin_port = htons(5010);

sockfd = socket(AF_INET,SOCK_STREAM,0);

if(connect(sockfd,(struct sockaddr*)&cliaddr, sizeof(cliaddr))<0){
printf("Problem with connection\n");
}


while(fgets(sendline, 1000, stdin)!=NULL)
{
send(sockfd,sendline,strlen(sendline),0);
if(recv(sockfd,recvline, 1000,0) ==0)
{
perror("The server terminated prematurely");
}
printf("%s","String received from the server:");
fputs(recvline, stdout);
}
exit(0);
}

