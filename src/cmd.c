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


cmd_T *
get_cmd()
{
	printf("> ");
	char buf[MAX_BUF] = {0};
	size_t n = 0;
	while ((buf[n++] = getchar()) != '\n') ;
	buf[n-1] = 0;

	size_t splits;
	char **tokens = split_by_ws(buf, &splits);
	for (size_t i = 0; i < splits; ++i)
		printf("TOK: %s\n", tokens[i]);
}

