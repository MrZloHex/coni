#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "tcp.h"


int
start_tcp
(
	int type,
	const char *ip,
	uint16_t port
)
{
	if (type == SERVER)
	{
		printf("STARTING SERVER ON PORT %hu\n", port);

	    	int sock_dscr;
	    	struct sockaddr_in server;
	    	struct sockaddr_in client;
		socklen_t namelen = sizeof(client);
	    	int ns;

	    	sock_dscr = socket(AF_INET, SOCK_STREAM, 0);
	    	if (sock_dscr == -1)
	    	{
			fprintf(stderr, "ERROR: failed to create a socket\n");
			exit(1);
	    	}

	    	server.sin_family      = AF_INET;
	    	server.sin_port        = htons(port);
	    	server.sin_addr.s_addr = INADDR_ANY;

    
	    	int n = bind(sock_dscr, (struct sockaddr *)&server, sizeof(server));
	    	if (n < 0)
	    	{
			fprintf(stderr, "ERROR: failed to bind socket\n");
	    		exit(1);
	    	}

	    	int res = listen(sock_dscr, 1);
	    	if (res != 0)
	    	{
			fprintf(stderr, "ERROR: failed to listen on socket\n");
	    		exit(1);
	    	}


	    	ns = accept(sock_dscr, (struct sockaddr *)&client, &namelen);
	    	if (ns == -1)
	    	{
			fprintf(stderr, "ERROR: failed to accept client req\n");
	    		exit(1);
	    	}
	    	return ns;
	}
	else if (type == CLIENT)
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
	    	server.sin_addr.s_addr = inet_addr(ip);
	    	server.sin_port = htons(port);

	    	int res = connect(sock_dscr, (struct sockaddr *)&server, sizeof(server));
	    	if (res != 0)
	    	{
			fprintf(stderr, "ERROR: failed to connect to server\n");
	    		exit(1);
	    	}
    
	    	return sock_dscr;
	} 
}


void
listen_tcp
(
	int fd,
    	char *buf,
    	size_t buflen
)
{
	read(fd, buf, buflen);
}

void
send_tcp
(
	int fd,
    	char *buf,
    	size_t buflen
)
{
	write(fd, buf, buflen);
}

void
stop_tcp(int server_fd)
{
	close(server_fd);
}
