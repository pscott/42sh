#include "libft.h"
#include "line_editing.h"

int					get_cols_term(void)
{
	struct winsize	s;

	ioctl(2, TIOCGWINSZ, &s);
	return (s.ws_col);
}

int					get_columns_display(int count, int maxlen)
{
	int				cols;

	cols = get_cols_term() / (maxlen + 1);
	if (!cols)
		cols = 1;
	if ((maxlen + 1) * count < get_cols_term())
		cols = count;
	return (cols);
}

int					get_rows_display(int count, int cols)
{
	if (count % cols == 0)
		return (count / cols);
	else
		return ((count / cols) + 1);
}

t_auto_comp			*ft_lst_swap(t_auto_comp *file1, t_auto_comp *file2)
{
	file1->next = file2->next;
	file2->next = file1;
	return (file2);
}

t_auto_comp			*ft_list_sort_ascii(t_auto_comp *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		lst = ft_lst_swap(lst, lst->next);
	lst->next = ft_list_sort_ascii(lst->next);
	if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
	{
		lst = ft_lst_swap(lst, lst->next);
		lst->next = ft_list_sort_ascii(lst->next);
	}
	return (lst);
}
