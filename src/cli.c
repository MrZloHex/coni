#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>

#include "cli.h"

void
usage()
{
	printf("USAGE\n");
	printf("  As server:\n");
	printf("\t$ coni -s [-p PORT]\n");
	printf("  As client:\n");
	printf("\t$ coni -s [-i IP]\n");
}

uint8_t
get_node_type
(
	const int argc,
	const char **argv
)
{
	if (argc < 2)
	{
		usage();
		fprintf(stderr, "ERROR: isn't provided type of node\n");
		exit(1);
	}

	if (strcmp(argv[1], "-s") == 0)
		return SERVER_NT;
	else if (strcmp(argv[1], "-c") == 0)
		return CLIENT_NT;
	else
	{
		usage();
		fprintf(stderr, "ERROR: invalid node type is provided: `%s`\n", argv[1]);
		exit(1);
	}
}

uint16_t
get_port
(
	const int argc,
	const char **argv
)
{
	if (argc < 4 && !(argc > 2))
	{
		return DEF_PORT;
	}
	
	if (strcmp(argv[2], "-p") == 0)
	{
		if (argc < 4)
		{
			usage();
			fprintf(stderr, "ERROR: port isn't provided\n");
			exit(1);
		}
		char *end;
		errno = 0;
		uintmax_t port = strtoumax(argv[3], &end, 10);
		if (errno == ERANGE || port < 0 || port > UINT16_MAX || end == argv[3] || *end != '\0')
		{
			usage();
			fprintf(stderr, "ERROR: failed to parse PORT: `%s`\n", argv[3]);
			exit(1);
		}
		else
		{
			return (uint16_t)port;
		}
	}
	else
	{
		usage();
		fprintf(stderr, "ERROR: unexpected argument: `%s`\n", argv[2]);
		exit(1);
	}
}
