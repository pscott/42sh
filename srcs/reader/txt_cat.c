#include "reader.h"

char	*concatenate_txt(t_st_cmd *st_cmd)
{
	char	*input;

	if (!st_cmd)
		return (NULL);
	while (st_cmd->prev)
		st_cmd = st_cmd->prev;
	input = NULL;
	while (st_cmd)
	{
		input = ft_strjoin(input, st_cmd->st_txt->txt);
		st_cmd = st_cmd->next;
	}
	return (input);
}
