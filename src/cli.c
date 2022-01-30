#include <string.h>

#include "cli.h"

uint8_t
get_node_type(const char *str)
{
	if (strcmp(str, "-s") == 0)
		return SERVER_NT;
	else if (strcmp(str, "-c") == 0)
		return CLIENT_NT;
	else
		return INVALD_NT;
}
