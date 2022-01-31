#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>

#include "cli.h"
#include "tcp.h"
#include "cmd.h"


void *
thread_listen(void *vargp)
{
	int *fd = (int *)vargp;
	while (M_PI)
	{
		char buf[200] = {0};
		listen_tcp(*fd, buf, 200);
		printf("\nshe > %s\nyou > ", buf);
	}
}

int
main
(
	int argc,
	const char *argv[]
)
{

	uint8_t nt = get_node_type(argc, argv);

	int conn;

	bool mode = 0;

	if (nt == SERVER_NT)
	{
		uint16_t port = get_port(argc, argv);
		conn = start_tcp(SERVER, NULL, port);
	}
	else if (nt == CLIENT_NT)
	{
		char ip[16] = {0};
		uint16_t port = get_ip_port(argc, argv, ip);
		conn = start_tcp(CLIENT, ip, port);
	}


	while (M_PI)
	{
		if (mode)
		{
			pthread_t tid;
			pthread_create(&tid, NULL, thread_listen, (void *)&conn);

			char buf[MAX_BUF] = {0};
			size_t n = 0;
			printf("you > ");
			while ((buf[n++] = getchar()) != '\n') ;
			buf[n-1] = 0;
			if (strcmp(buf, "!exit") == 0)
			{
				mode = 0;
				pthread_exit(NULL);
			}
			
			send_tcp(conn, buf, n);
		}
		else
		{
			cmd_T cmd = get_cmd();
			if (cmd.type == EXIT)
			{
				printf("TCP OFF\n");
				stop_tcp(conn);
				exit(0);
			}
			else if (cmd.type == SEND)
			{
				printf("Sending messsage `%s`\n", cmd.data);
				send_tcp(conn, cmd.data, 20);
			}
			else if (cmd.type == LISTEN)
			{
				printf("Listening...\n");
				char buf[200] = {0};
				listen_tcp(conn, buf, 200);
				printf("GOT A MSG: `%s`\n", buf);
			}
			else if (cmd.type == MODE)
			{
				if (cmd.sub_type == CHAT)
					mode = 1;
				else if (cmd.sub_type == CMD)
					mode = 0;
			}
		}
	}
	return 0;
}
