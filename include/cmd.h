#ifndef CMD_H_
#define CMD_H_

#define MAX_BUF 256

typedef enum
{
	INVALID,
	EXIT,
	SEND,
	LISTEN
} cmd_type_T;

typedef struct
{
	cmd_type_T type;
	char *data;
} cmd_T;

cmd_T
get_cmd();

#endif /* CMD_H_ */
