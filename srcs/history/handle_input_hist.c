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
	if (isatty(STDIN_FILENO) == 0)
		return ;
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	insert_left(st_cmd->hist_lst, line, 1);
}
