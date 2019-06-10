#include "input.h"

char	*concatenate_txt(t_st_cmd *st_cmd, int heredoc)
{
	char	*input;
	char	*tmp;

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
		tmp = input;
		if (!(input = ft_strjoin(input, st_cmd->st_txt->txt)))
			clean_exit(1, 1);
		ft_strdel(&tmp);
		st_cmd = st_cmd->next;
	}
	return (input);
}
