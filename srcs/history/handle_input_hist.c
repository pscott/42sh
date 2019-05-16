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

void	adjust_history(t_st_cmd *st_cmd, char *line) // what does it do ? when no hist ?
{
	t_hist_lst	*to_insert;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (st_cmd->hist_lst->prev)
		to_insert = st_cmd->hist_lst->prev;
	else
		to_insert = st_cmd->hist_lst;
	if (to_insert->keep)
		insert_right(to_insert, line, 0);
	else
	{
		ft_strdel(&to_insert->txt);
		ft_strdel(&to_insert->cpy);
		if (!(to_insert->txt = ft_strdup(line)))
			ERROR_MEM;
		if (!(to_insert->cpy = ft_strdup(line)))
			ERROR_MEM;
	}
}
