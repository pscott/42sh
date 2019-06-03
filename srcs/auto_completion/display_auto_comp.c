#include "auto_completion.h"

static void	real_display_various(t_auto_comp *tmp, unsigned int count,
			int cols, int rows)
{
	unsigned int	maxlen;
	t_auto_comp		*first;
	int				i;
	int				j;
	int				rows_save;

	maxlen = get_max_len(tmp);
	first = tmp;
	i = -1;
	while (++i < rows && tmp)
	{
		j = -1;
		while (++j < cols && count > 0 && tmp)
		{
			rows_save = rows;
			ft_putstr(tmp->name);
			print_spaces(tmp->name, maxlen);
			--count;
			while (tmp && rows_save--)
				tmp = tmp->next;
		}
		if (first && first->next && (first = first->next))
			tmp = first;
		ft_putchar('\n');
	}
}

static int	display_various(t_auto_comp *match, char **ret,
			const char *to_find)
{
	int				cols;
	unsigned int	count;
	int				rows;

	count = len_lst(match);
	if (to_find)
		*ret = ft_strdup(to_find);
	if (count > MAX_DISPLAY)
		if ((is_display(count)) == 1)
			return (1);
	ft_putchar('\n');
	while (match->prev)
		match = match->prev;
	cols = get_columns_display(count, get_max_len(match));
	rows = get_rows_display(count, cols);
	while (match->prev)
		match = match->prev;
	real_display_various(match, count, cols, rows);
	return (0);
}

static int	lst_match_more_than_to_find(t_auto_comp *match, unsigned int len)
{
	int				ret;
	int				len_to_find;
	t_auto_comp		*curr;

	ret = 0;
	len_to_find = 0;
	while (match->prev)
		match = match->prev;
	curr = match;
	if (ret > 0)
		ret--;
	ret = len;
	while (curr->name && curr->name[ret] && curr->next)
	{
		curr = curr->next;
		if (curr->name[ret] != match->name[ret])
			return (ret - len);
		if (!curr->next)
		{
			curr = match;
			ret++;
		}
	}
	return (ret - len);
}

static void	my_ft_list_sort(t_auto_comp **begin_list)
{
	t_auto_comp		*current;
	t_auto_comp		*current2;
	char			*next;

	current = NULL;
	if (!begin_list || !*begin_list)
		return ;
	while ((*begin_list)->prev)
		(*begin_list) = (*begin_list)->prev;
	current = *begin_list;
	while (current)
	{
		current2 = *begin_list;
		while (current2->next)
		{
			if (ft_strcmp(current2->name, current2->next->name) > 0)
			{
				next = current2->name;
				current2->name = current2->next->name;
				current2->next->name = next;
			}
			current2 = current2->next;
		}
		current = current->next;
	}
}

char		*get_ret_or_display_matches(t_auto_comp *match,
			const char *to_find, unsigned int len)
{
	int				diff_len;
	char			*ret_str;
	int				is_empty_last_c;

	ret_str = NULL;
	is_empty_last_c = 0;
	my_ft_list_sort(&match);
	if (len_lst(match) == 1)
		ret_str = ft_strdup(match->name);
	else if ((diff_len = lst_match_more_than_to_find(match, len)) > 0)
	{
		if (match->name[diff_len] && (match->name[diff_len] == ' '
					|| match->name[diff_len] == '/'))
			is_empty_last_c = 1;
		if (!(ret_str = ft_strndup(match->name, len + diff_len
						- is_empty_last_c)))
			ERROR_MEM;
	}
	else
	{
		display_various(match, &ret_str, to_find);
	}
	del_match(match);
	return (ret_str);
}
