#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cli.h"
#include "server.h"
#include "client.h"
#include "cmd.h"



int
main
(
	int argc,
	const char *argv[]
)
{

	uint8_t nt = get_node_type(argc, argv);

	if (nt == SERVER_NT)
	{
		uint16_t port = get_port(argc, argv);
		start_server(port);
		while (M_PI)
		{
			cmd_T cmd = get_cmd();
			if (cmd.type == EXIT)
			{
				printf("SERVER OFF\n");
				//stop_server();
				exit(0);
			}
			else if (cmd.type == SEND)
			{
				printf("Sending messsage `%s`\n", cmd.data);
			}
		}
	}
	else if (nt == CLIENT_NT)
	{
		char ip[16] = {0};
		uint16_t port = get_ip_port(argc, argv, ip);
		start_client(ip, port);
		while (M_PI)
		{
			cmd_T cmd = get_cmd();
			if (cmd.type == EXIT)
			{
				printf("SERVER OFF\n");
				//stop_server();
				exit(0);
			}
			else if (cmd.type == SEND)
			{
				printf("Sending messsage `%s`\n", cmd.data);
			}
		}
	}


	return 0;
}
