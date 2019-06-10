#include "input.h"

char	*concatenate_txt(t_st_cmd *st_cmd, int heredoc)
{
	char	*input;

	if (!st_cmd)
		return (NULL);
	st_cmd = get_first_st_cmd(st_cmd);
	if (heredoc)
	{
		st_cmd = st_cmd->next;
		if (!(input = ft_strdup("\n")))
			clean_exit(1, 1);
	}
	else
		input = NULL;
	while (st_cmd)
	{
		if (!(input = ft_strjoin_free_left(input, st_cmd->st_txt->txt)))
			clean_exit(1, 1);
		st_cmd = st_cmd->next;
	}
	return (input);
}
