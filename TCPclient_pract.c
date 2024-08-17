#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>

//int main()
int main(int argc, char const* argv[])
{

int sockfd = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in cliaddr;

cliaddr.sin_family = AF_INET;
cliaddr.sin_port = htons(9005);
cliaddr.sin_addr.s_addr = INADDR_ANY;

int conn_id = connect(sockfd,(struct sockaddr*)&cliaddr, sizeof(cliaddr));

if (conn_id == -1)
{
	printf("Problem with TCP connection establishment\n");
}
else
{

	char rbuff[255];
	recv(conn_id,rbuff,sizeof(rbuff),0);
        printf("The received message from server is:%s\n", rbuff);
}
return 0;
}
