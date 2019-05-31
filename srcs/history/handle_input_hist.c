#include "42sh.h"
#include "line_editing.h"
#include "history.h"

t_hist_lst	*get_keep(t_hist_lst *hist_lst)
{
	t_hist_lst *probe;

	if (!(probe = hist_lst))
		return (NULL);
	while (probe->keep)
		probe = probe->next;
	return (probe);
}

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
			ERROR_MEM;
		ft_strdel(&left->cpy);
		if (!(left->cpy = ft_strdup(line)))
			ERROR_MEM;
	}
}

/*
**	Appends a history node to the left of the last history node.
**	If keep is zero, simply works on left node and join the left node content
**	and line parameter.
**	If keep is 1, replace the temporary content with a definitive content.
*/

void		adjust_history(t_st_cmd *st_cmd, const char *line, int keep)
{
	t_hist_lst *left;

	if (isatty(STDIN_FILENO) == 0)
		return ;
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
			ERROR_MEM;
		ft_strdel(&left->cpy);
		if (!(left->cpy = ft_strdup(line)))
			ERROR_MEM;
		left->keep = 1;
	}
	else
		insert_left(st_cmd->hist_lst, line, keep);
}
