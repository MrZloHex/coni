#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cli.h"
#include "tcp.h"
#include "cmd.h"



int
main
(
	int argc,
	const char *argv[]
)
{

	uint8_t nt = get_node_type(argc, argv);

	int me;


	if (nt == SERVER_NT)
	{
		uint16_t port = get_port(argc, argv);
		me = start_tcp(SERVER, NULL, port);
	}
	else if (nt == CLIENT_NT)
	{
		char ip[16] = {0};
		uint16_t port = get_ip_port(argc, argv, ip);
		me = start_tcp(CLIENT, ip, port);
	}


	while (M_PI)
		{
			cmd_T cmd = get_cmd();
			if (cmd.type == EXIT)
			{
				printf("SERVER OFF\n");
				stop_tcp(me);
				exit(0);
			}
			else if (cmd.type == SEND)
			{
				printf("Sending messsage `%s`\n", cmd.data);
				send_tcp(me, cmd.data, strlen(cmd.data));
			}
			else if (cmd.type == LISTEN)
			{
				printf("Listening...\n");
				char buf[200] = {0};
				listen_tcp(me, buf, 200);
				printf("GOT A MSG: `%s`\n", buf);
			}
		}


	return 0;
}
