#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>

//int main()
int main(int argc, char const* argv[])
{

int servsockid = socket(AF_INET,SOCK_STREAM,0);
char Msg[255] = "Welcome to reprogram the IPC and get trained";


struct sockaddr_in serveraddr;

serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(9005);
serveraddr.sin_addr.s_addr = INADDR_ANY;

bind(servsockid, (struct sockaddr*)&serveraddr,sizeof(serveraddr));

listen(servsockid,1);

int clientsockid = accept(servsockid,NULL, NULL);

send(clientsockid,Msg, sizeof(Msg),0);

return 0;
}




