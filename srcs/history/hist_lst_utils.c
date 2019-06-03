#include "ftsh.h"
#include "history.h"

t_hist_lst	*create_hist_lst(const char *line, char keep)
{
	t_hist_lst	*res;

	if (!(res = (t_hist_lst*)malloc(sizeof(*res))))
		ERROR_MEM;
	if (!(res->txt = ft_strdup(line)))
		ERROR_MEM;
	if (!(res->cpy = ft_strdup(line)))
		ERROR_MEM;
	res->keep = keep;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void		free_hist_lst(t_hist_lst *hist_lst)
{
	t_hist_lst *tmp;
	t_hist_lst *probe;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (!hist_lst)
		return ;
	probe = get_begin_lst(hist_lst);
	while (probe)
	{
		tmp = probe;
		probe = probe->next;
		ft_strdel(&tmp->txt);
		ft_strdel(&tmp->cpy);
		ft_memdel((void*)&tmp);
	}
}

/*
** Debugging function
*/

void		print_hist_lst(t_hist_lst *hist_lst)
{
	t_hist_lst *probe;

	probe = get_begin_lst(hist_lst);
	ft_printf("--- PRINTING LST --- \n");
	while (probe)
	{
		ft_printf("PROBE: TXT: {%s}\n", probe->txt);
		probe = probe->next;
	}
}
