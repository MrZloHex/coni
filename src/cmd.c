#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmd.h"

char **
split_by_ws
(
	const char *str,
	size_t *sps
)
{
	size_t splits = 0;
	for (size_t i = 0; i < strlen(str); ++i)
		if (str[i] == ' ')
			splits++;

	if (str[strlen(str)-1] == ' ')
		*sps = splits;
	else
		*sps = ++splits;

	char **strv = (char **)calloc(1, sizeof(char *)*splits);
	size_t last_split = 0;
	size_t split_i = 0;
	for (size_t i = 0; i < strlen(str)+1; ++i)
	{
		if (str[i] == ' ' || str[i] == 0)
		{
			size_t str_len = i - last_split;
			strv[split_i] = (char *)calloc(1, sizeof(char)*(str_len + 1));
			strncpy(strv[split_i++], str+last_split, str_len);
			last_split = i+1;
		}
	}
	return strv;
}


cmd_T
get_cmd()
{
	printf("> ");
	char buf[MAX_BUF] = {0};
	size_t n = 0;
	while ((buf[n++] = getchar()) != '\n') ;
	buf[n-1] = 0;

	size_t splits;
	char **tokens = split_by_ws(buf, &splits);
	
	if (strcmp(tokens[0], "EXIT") == 0 || strcmp(tokens[0], "exit") == 0)
	{
		cmd_T cmd = {
			.type = EXIT,
			.sub_type = NONE,
			.data = 0
		};
		return cmd;
	}
	else if (strcmp(tokens[0], "SEND") == 0 || strcmp(tokens[0], "send") == 0)
	{
		cmd_T cmd = {
			.type = SEND,
			.sub_type = NONE,
			.data = tokens[1]
		};
		return cmd;
	}
	else if (strcmp(tokens[0], "LISTEN") == 0 || strcmp(tokens[0], "listen") == 0)
	{
		cmd_T cmd = {
			.type = LISTEN,
			.sub_type = NONE,
			.data = 0
		};
		return cmd;
	}
	else if (strcmp(tokens[0], "MODE") == 0 || strcmp(tokens[0], "mode") == 0)
	{
		if (strcmp(tokens[1], "CHAT") == 0 || strcmp(tokens[1], "chat") == 0)
		{
			cmd_T cmd = {
				.type = MODE,
				.sub_type = CHAT,
				.data = 0
			};
			return cmd;
		}
		else if (strcmp(tokens[1], "CMD") == 0 || strcmp(tokens[1], "cmd") == 0)
		{
			cmd_T cmd = {
				.type = MODE,
				.sub_type = CMD,
				.data = 0
			};
			return cmd;
		}
		else
		{
			fprintf(stderr, "ERROR: incorrect subcommand for MODE is possible [CHAT|CMD] tou provided: `%s`\n", tokens[1]);
			cmd_T cmd = {
				.type = INVALID,
				.sub_type = NONE,
				.data = 0
			};
			return cmd;
		}
	}
	else
	{
		fprintf(stderr, "ERROR: incorrect command `%s`\n", tokens[0]);
		cmd_T cmd = {
			.type = INVALID,
			.sub_type = NONE,
			.data = 0
		};
		return cmd;
	}
}

