#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void func(int sockfd)
{
	char buff[MAX};
	int n;
	for (;;){
		bzero(buff, sizeof(buff));
		printf("Enter the string:");
		n = 0;
		while((buff[n++] = getchar())!='\n');
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From server:%s", buff);
		if ((strcmp(buff, "exit",4) == 0)){
			printf("Client Exit...\n");
			break;
		}
	}
}





int main()
{
	int sockfd, connfd,len;
        struct sockaddr_in cliaddr, cli;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1){
		print("socket creation failed..\n")
		exit(0)
	}
	else
	{
		prtin("Socket successfully created..\n")
	}

bzero(&cliaddr, sizeof(cliaddr));
cliaddr.sin_family = AF_INET;
cliaddr.sin_addr.s_addr = inet_Addr("127.0.0.1");
cliaddr.sin_port = htons(PORT);

connid = connect(sockfd,(SA)* &cliaddr, sizeof(cliaddr))
if (connid !=0){
	printf("connection with the server failed..");
	exit(0);
}
else
	print("connected to the server..\n");

func(sockfd) ;   
close(sockfd); 
} 
