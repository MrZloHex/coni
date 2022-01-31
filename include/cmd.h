#ifndef CMD_H_
#define CMD_H_

#define MAX_BUF 256

typedef enum
{
	INVALID,
	EXIT,
	SEND,
	LISTEN,
	MODE
} cmd_type_T;

typedef enum
{
	NONE,
	CHAT,
	CMD
} cmd_sub_type_T;

typedef struct
{
	cmd_type_T type;
	cmd_sub_type_T sub_type;
	char *data;
} cmd_T;

cmd_T
get_cmd();

#endif /* CMD_H_ */
