#include "libft.h"
#include "line_editing.h"
#include "libterm.h"

static void	real_display_various(t_auto_comp *tmp, unsigned int count, int cols, int rows)
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
		print_line();
	}
}

static int	display_various(t_auto_comp *match)
{
	int				cols;
	unsigned int	count;
	int				rows;

	count = len_lst(match);
	if (count > MAX_DISPLAY)
		if ((is_display(count)) == 1)
			return (1);
	print_line();
	cols = get_columns_display(count, get_max_len(match));
	if ((rows = get_rows_display(count, cols)) == 1 && count <= MAX_DISPLAY)
		print_line();
	while (match->prev)
		match = match->prev;
	real_display_various(match, count, cols, rows);
	return (0);
}

int			lst_match_more_than_to_find(t_auto_comp *match, unsigned int len)
{
	int				ret;
	int				len_to_find;
	t_auto_comp		*curr;
/*
ft_putnbr(len);
sleep(3);
*/
	ret = 0;
	len_to_find = 0;
	while (match->prev)
		match = match->prev;
	curr = match;
	if (ret > 0)
		ret--;
	
	ret = len;
	ft_printf("name : |%s|, ret: %d", curr->name, ret);
	sleep(2);
	
	while (curr->name && curr->name[ret] && curr->next)
	{
		ft_putendl(curr->name);
		usleep(100);
		curr = curr->next;
		if (curr->name[ret]	!= match->name[ret])
			return (ret - len);
		if (!curr->next)
		{
			curr = match;
			ret++;
		}
	}

	return (ret - 1);
}

char		*get_ret_or_display_matches(t_auto_comp *match, char *to_find, unsigned int len)
{
	int				diff_len;
	char			*ret_str;
	int				is_empty_last_c;
/*
ft_putendl(to_find);
sleep(2);
*/
//	ft_list_sort_ascii(match); //TODO
/*
	ft_printf("str {%s} len {%u}", to_find, len);
	sleep(2);
	*/
	ret_str = NULL;
	is_empty_last_c = 0;
	while (match->prev)
		match = match->prev;
	if (len_lst(match) == 1)
	{

		ft_putendl("EIOWIOEWIOW");
		sleep(1);
		ret_str = ft_strdup(match->name);
	}

	else if ((diff_len = lst_match_more_than_to_find(match, len)) > 0)
	{
		ft_putnbr(diff_len);
		sleep(1);
		if (match->name[diff_len] && (match->name[diff_len] == ' ' || match->name[diff_len] == '/'))
			is_empty_last_c = 1;
		if (!(ret_str = ft_strndup(match->name, len + diff_len - is_empty_last_c)))
			ERROR_MEM
	}
	else
	{
		ft_putendl("ZZZZZ");
		sleep(1);
		display_various(match);
		if (to_find)
			ret_str = ft_strdup(to_find);
	}
	del_match(match);
	/*
	ft_printf("REEE |%s|", ret_str);
	sleep(2);
	*/
	return (ret_str);
}
