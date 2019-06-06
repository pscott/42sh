#include "input.h"

char	*concatenate_txt(t_st_cmd *st_cmd)
{
	char	*input;
	char	*tmp;

	if (!st_cmd)
		return (NULL);
	while (st_cmd->prev)
		st_cmd = st_cmd->prev;
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
