#include "libft.h"
#include "line_editing.h"
#include <sys/ioctl.h>

unsigned int		get_cols_term(void)
{
	struct winsize	s;

	ioctl(2, TIOCGWINSZ, &s);
	return (s.ws_col);
}

unsigned int		get_columns_display(unsigned int count, unsigned int maxlen)
{
	unsigned int	cols;

	cols = get_cols_term() / (maxlen + 1);
	if (!cols)
		cols = 1;
	if ((maxlen + 1) * count < get_cols_term())
		cols = count;
	return (cols);
}

unsigned int		get_rows_display(unsigned int count, unsigned int cols)
{
	if (count % cols == 0)
		return (count / cols);
	else
		return ((count / cols) + 1);
}

void				*ft_lst_swap(t_auto_comp **l1, t_auto_comp **l2)
{
	t_auto_comp		*tmp;

	tmp = *l2;
	*l2 = *l1;
	*l1 = tmp;
}

t_auto_comp			*ft_list_sort_ascii(t_auto_comp **lst)
{
	if (!lst || !(*lst))
		return (NULL);
	if ((*lst)->next && ft_strcmp((*lst)->name, (*lst)->next->name) > 0)
		(*lst) = ft_lst_swap(*lst, (*lst)->next);
	(*lst)->next = ft_list_sort_ascii(&((*lst)->next));
	if ((*lst)->next && ft_strcmp((*lst)->name, (*lst)->next->name) > 0)
	{
		(*lst) = ft_lst_swap((*lst), (*lst)->next);
		(*lst)->next = ft_list_sort_ascii(&((*lst)->next));
	}
	return (*lst);
}
