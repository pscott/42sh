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

void	adjust_history(t_st_cmd *st_cmd, char *line)
{
	t_hist_lst	*to_insert;

	if (st_cmd->hist_lst->prev)
		to_insert = st_cmd->hist_lst->prev;
	else
		to_insert = st_cmd->hist_lst;
	if (to_insert->keep)
		insert_right(to_insert, line, 0);
	else
	{
		ft_memdel((void*)&to_insert->txt);
		to_insert->cpy = ft_strdup(line);
	}
}
