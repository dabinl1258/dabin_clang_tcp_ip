#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc , char ** argv)
{
	int sockfd = 0 ;
	struct sockaddr_in  serv_addr;
	char recvBuffer[255];
	int port;



	if ( argc < 3) 
	{
		printf("\nfew argument \n");
	}
	port = atoi(argv[2]);
	memset(&serv_addr, '0' , sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port  = htons(port);
	
    sockfd = socket(AF_INET , SOCK_STREAM, 0);

	if (sockfd < 0 )
		printf("Coudl Create socket\n");
	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr)<= 0)
	{
		printf("Could not find host \n");
		return 0;
	}

	inet_pton(AF_INET, argv[1], recvBuffer);
	printf("big-endian address %s\n", recvBuffer);


	if(connect(sockfd , (struct sockaddr_in*)&serv_addr , sizeof(serv_addr)) <0 )
	{
		printf("connect false\n");
		return 0;
	}
	printf("connected\n");

	recv(sockfd, recvBuffer,sizeof(recvBuffer), 0);
	printf("recved string %s\n", recvBuffer);

	close(sockfd);
	return 0;
}
