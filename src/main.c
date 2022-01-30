#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "server.h"
#include "client.h"


void
usage()
{
	printf("USAGE\n");
	printf("  As server:\n");
	printf("\t$ coni -s [-p PORT]\n");
	printf("  As client:\n");
	printf("\t$ coni -s [-i IP]\n");
}


int
main
(
	int argc,
	char *argv[]
)
{
	if (argc < 2)
	{
		usage();
		fprintf(stderr, "ERROR: isn't provided type of node\n");
		exit(1);
	}

	uint8_t nt = get_node_type(argv[1]);
	if (nt == INVALD_NT)
	{
		usage();
		fprintf(stderr, "ERROR: invalid node type is provided: `%s`\n", argv[1]);
		exit(1);
	}

	if (nt == SERVER_NT)
	{
		start_server();
	}
	else if (nt == CLIENT_NT)
	{
		start_client();
	}








	return 0;
}
