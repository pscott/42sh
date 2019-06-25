#include "input.h"
#include "cmd_parsing.h"

/*
**	Returns a string containing all string contents in the st_cmd list.
*/

char	*concatenate_txt(t_st_cmd *st_cmd, int mode)
{
	char	*input;
	char	*tmp;

	if (!st_cmd)
		return (NULL);
	st_cmd = get_first_st_cmd(st_cmd);
	if (!(input = ft_strdup("")))
		clean_exit(1, 1);
	while (st_cmd)
	{
		if (!(tmp = ft_strdup(st_cmd->st_txt->txt)))
			clean_exit(1, 1);
		if (mode == 1 && replace_bang(&(st_cmd->st_txt->txt), 1))
		{
			free(input);
			if (!(input = ft_strnew(0)))
				clean_exit(1, 1);
			ft_strdel(&tmp);
			return (input);
		}
		if (!ft_strequ(st_cmd->st_txt->txt, tmp))
			ft_dprintf(1, "%s", st_cmd->st_txt->txt);
		if (!(input = ft_strjoin_free_left(input, st_cmd->st_txt->txt)))
			clean_exit(1, 1);
		ft_strdel(&tmp);
		st_cmd = st_cmd->next;
	}
	return (input);
}

char	*concatenate_heredoc_txt(t_st_cmd *st_cmd, t_st_cmd *start)
{
	char	*input;

	if (!st_cmd)
		return (NULL);
	st_cmd = get_first_st_cmd(st_cmd);
	while (st_cmd != start)
		st_cmd = st_cmd->next;
	if (!(input = ft_strdup("\n")))
		clean_exit(1, 1);
	while (st_cmd)
	{
		input = ft_strjoin_free_left(input, st_cmd->st_txt->txt);
		st_cmd = st_cmd->next;
	}
	return (input);
}
