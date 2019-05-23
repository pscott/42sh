#include "42sh.h"
#include "history.h"

t_hist_lst	*create_hist_lst(const char *line, char keep)
{
	t_hist_lst	 *res;

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

t_hist_lst	*get_begin_lst(t_hist_lst *hist_lst)
{
	if (!hist_lst)
		return (NULL);
	else
		while (hist_lst->prev)
			hist_lst = hist_lst->prev;
	return (hist_lst);
}

t_hist_lst	*get_end_lst(t_hist_lst *hist_lst)
{
	if (!hist_lst)
		return (NULL);
	else
		while (hist_lst->next)
			hist_lst = hist_lst->next;
	return (hist_lst);
}

t_hist_lst		*insert_left(t_hist_lst *hist_lst, const char *line, char keep)
{
	t_hist_lst	*probe;
	t_hist_lst	*insert;

	insert = create_hist_lst(line, keep);
	if (!(probe = hist_lst))
		return (insert);
	else
	{
		if (probe->prev)
		{
			probe->prev->next = insert;
			insert->prev = probe->prev;
		}
		insert->next = probe;
		probe->prev = insert;
	}
	return (insert);
}

t_hist_lst	*insert_right(t_hist_lst *hist_lst, const char *line, char keep)
{
	t_hist_lst	*probe;
	t_hist_lst	*insert;

	insert = create_hist_lst(line, keep);
	if (!(probe = hist_lst))
		return (insert);
	else
	{
		if (probe->next)
		{
			probe->next->prev = insert;
			insert->next = probe->next;
		}
		probe->next = insert;
		insert->prev = probe;
	}
	return (insert);
}

// debug
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
