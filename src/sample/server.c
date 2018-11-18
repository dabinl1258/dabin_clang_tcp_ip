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
	int listenfd =0 , connectfd = 0;
	struct sockaddr_in  serv_addr;
	char sendBuffer[255];
	int port;

	time_t ticks;
	
	if ( argc < 2)
	{
		printf(" few argument \n");
		return 0;
	}
	
	listenfd = socket(AF_INET, SOCK_STREAM,0 );

	memset(&serv_addr, 0 , sizeof(serv_addr));
	memset(&sendBuffer , 0 , sizeof(sendBuffer));
	port = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	if (bind(listenfd , (struct sockaddr *)&serv_addr,   sizeof(serv_addr)) < 0)
	{
		printf("bind false\n");
		return 0;
	}

	listen(listenfd , 10);
	

	connectfd = accept(listenfd , (struct  sockaddr *)NULL  , NULL);
	printf("accepted \n");

	sprintf(sendBuffer, "hi you");
	send(connectfd , sendBuffer, sizeof(sendBuffer), 0);
	

	close(connectfd);
	return 0;
}
