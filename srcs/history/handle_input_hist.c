#include "ftsh.h"
#include "line_editing.h"
#include "history.h"

static void	update_temporary_hist(t_hist_lst *hist_lst, const char *line)
{
	t_hist_lst *left;

	left = hist_lst->prev;
	if (!left || left->keep == 1)
		insert_left(hist_lst, line, 0);
	else
	{
		ft_strdel(&left->txt);
		if (!(left->txt = ft_strdup(line)))
			clean_exit(1, 1);
		ft_strdel(&left->cpy);
		if (!(left->cpy = ft_strdup(line)))
			clean_exit(1, 1);
	}
}

/*
**	Appends a history node to the left of the last history node.
**	If keep is zero, simply works on left node and join the left node content
**	and line parameter.
**	If keep is 1, replace the temporary content with a definitive content.
*/

void		adjust_history(t_st_cmd *st_cmd, int keep)
{
	t_hist_lst	*left;
	char		*line;

	if (isatty(TERM_FD) == 0)
		return ;
	line = concatenate_txt(st_cmd);
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	left = st_cmd->hist_lst->prev;
	if (keep == 0)
		update_temporary_hist(st_cmd->hist_lst, line);
	else if (!left)
		insert_left(st_cmd->hist_lst, line, 1);
	else if (left->keep == 0)
	{
		ft_strdel(&left->txt);
		if (!(left->txt = ft_strdup(line)))
			clean_exit(1, 1);
		ft_strdel(&left->cpy);
		if (!(left->cpy = ft_strdup(line)))
			clean_exit(1, 1);
		left->keep = 1;
	}
	else
		insert_left(st_cmd->hist_lst, line, keep);
	ft_strdel(&line);
}
