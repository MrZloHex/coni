#ifndef CLI_H_
#define CLI_H_

#include <stdint.h>

#define DEF_PORT 8080

void
usage();

#define INVALD_NT 1
#define SERVER_NT 2
#define CLIENT_NT 3

uint8_t
get_node_type
(
	const int argc,
	const char **argv
);

uint16_t
get_port
(
	const int argc,
	const char **argv
);


#endif /* CLI_H_ */
