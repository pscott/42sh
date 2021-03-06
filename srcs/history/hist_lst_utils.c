#include "ftsh.h"
#include "history.h"

t_hist_lst	*create_hist_lst(const char *line, char keep)
{
	t_hist_lst	*res;
	char		*tmp;

	if (!(isatty(TERM_FD)))
		return (NULL);
	if (!(res = (t_hist_lst*)malloc(sizeof(*res))))
		clean_exit(1, MALLOC_ERR);
	if (!ft_strchr(line, '\n'))
	{
		if (!(tmp = ft_strjoin(line, "\n")))
			clean_exit(1, MALLOC_ERR);
	}
	else if (!(tmp = ft_strdup(line)))
		clean_exit(1, MALLOC_ERR);
	if (!(res->txt = ft_strdup(tmp)))
		clean_exit(1, MALLOC_ERR);
	if (!(res->cpy = ft_strdup(tmp)))
		clean_exit(1, MALLOC_ERR);
	ft_strdel(&tmp);
	res->keep = keep;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void		free_hist_lst(t_hist_lst *hist_lst)
{
	t_hist_lst *tmp;
	t_hist_lst *probe;

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
	ft_dprintf(TERM_FD, "--- PRINTING LST --- \n");
	while (probe)
	{
		ft_dprintf(TERM_FD, "PROBE: TXT: {%s}\n", probe->txt);
		probe = probe->next;
	}
}
