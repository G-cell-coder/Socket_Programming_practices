#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>

void* clienthread(void* args)
{
int client_request = *((int*)args);
int network_socket;
network_socket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_addr.s_addr = INADDR_ANY;
serverAddress.sin_port = htons(8989);
//int serverAddress1 = strlen(serverAddress);
int connection_status = connect(network_socket,(struct sockaddr*)&serverAddress,sizeof(serverAddress));


if (connection_status <0){
	puts("Error\n");
	return 0;
}
printf("Connection estalished\n");

send(network_socket, & client_request, sizeof(client_request),0);
close(network_socket);
pthread_exit(NULL);
return 0;
}

int main()
{

printf("1.Read\n");
printf("2.Write\n");
int choice;
scanf("%d", & choice);
pthread_t tid;

switch(choice){
case 1:{
	int client_request = 1;
	pthread_create(&tid, NULL, clienthread, &client_request);
	sleep(20);
	break;
}
case 2:{
	int client_request = 2;
	pthread_create(&tid, NULL, clienthread, &client_request);
	sleep(20);
	break;
}
default:
	printf("Invalid Input\n");
	break;
}

pthread_join(tid, NULL);
}
