#ifndef CLI_H_
#define CLI_H_

#include <stdint.h>

#define INVALD_NT 1
#define SERVER_NT 2
#define CLIENT_NT 3

uint8_t
get_node_type(const char *str); 



#endif /* CLI_H_ */
