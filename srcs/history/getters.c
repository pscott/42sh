#include "ftsh.h"
#include "history.h"

t_hist_lst		*get_begin_lst(t_hist_lst *hist_lst)
{
	if (!hist_lst)
		return (NULL);
	else
		while (hist_lst->prev)
			hist_lst = hist_lst->prev;
	return (hist_lst);
}

t_hist_lst		*get_end_lst(t_hist_lst *hist_lst)
{
	if (!hist_lst)
		return (NULL);
	else
		while (hist_lst->next)
			hist_lst = hist_lst->next;
	return (hist_lst);
}

int				get_hist_len(t_hist_lst *hist_lst)
{
	int			i;

	if (!hist_lst)
		return (0);
	else
	{
		i = 0;//avant, = 1;
		hist_lst = get_begin_lst(hist_lst);
		while (hist_lst->next)//avant, juste hist_lst
		{
			i++;
			hist_lst = hist_lst->next;
		}
		if (i != 0)
			i++;
		if (hist_lst && hist_lst->txt && !ft_strequ(hist_lst->txt, "last"))
			i++;// archi sale, mais j'arrive pas
		return (i);
	}
}

t_hist_lst		*get_entry_lst(t_hist_lst *hist_lst, int index)
{
	if (!(hist_lst = get_begin_lst(hist_lst)))
		return (NULL);
	while (index-- > 1 && hist_lst->next)
		hist_lst = hist_lst->next;
	return (hist_lst);
}
