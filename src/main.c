#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "server.h"
#include "client.h"




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
	}
	else if (nt == CLIENT_NT)
	{
		start_client();
	}


	return 0;
}
