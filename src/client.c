#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"

void
start_client()
{
	printf("STARTING CLIENT\n");

	int sock_dscr;
	struct sockaddr_in server;

	sock_dscr = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_dscr == -1)
	{
		fprintf(stderr, "ERROR: failed to create a socket\n");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8080);

	int res = connect(sock_dscr, (struct sockaddr *)&server, sizeof(server));
	if (res != 0)
	{
		fprintf(stderr, "ERROR: failed to connect to server\n");
		exit(1);
	}
	
	close(sock_dscr);
}
