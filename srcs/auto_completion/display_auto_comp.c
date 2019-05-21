#include "libft.h"
#include "line_editing.h"
#include "libterm.h"

static int	len_lst(t_auto_comp *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->prev != NULL)
		lst = lst->prev;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static int	get_max_len(t_auto_comp *match)
{
	t_auto_comp		*tmp;
	unsigned int	max;

	if (!match)
		return (0);
	max = 0;
	tmp = match;
	while (tmp->prev)
	{
		tmp = tmp->prev;
	}
	max = tmp->len;
	while (tmp)
	{
		if (tmp->len > max)
			max = tmp->len;
		tmp = tmp->next;
	}
	return (max);
}

static int	is_display(int count)
{
	char			c;

//	signal(SIGINT, SIG_IGN);//faire un handler pour Ctrl C
	print_line();
	ft_printf("Display all %d possibilities? (y or n)", count);		
	while (1)
	{
		read(0, &c, 1);
		if (c == 'n' || c == 'N' || c == 127)
		{
			return (1);
		}
		else if (c == 'y' || c == 'Y' || c == 32)
		{
			return (0);
		}
	}	
}

static void	print_spaces(char *s, int cols)
{
	int				len;

	len = ft_strlen(s);
	if (cols == 1)
	{
		while (++len < cols)
			ft_putstr(" ");
	}
	else
	{
		while (len++ <= cols)
			ft_putstr(" ");
	}

}

static int	display_various(t_auto_comp *match)
{
	int				maxlen;
	int				cols;
	int				count;
	int				rows;
	int				i;
	int				j;
	int				rows_save;
	t_auto_comp		*tmp;
	t_auto_comp		*first;

	count = len_lst(match);
	if (count > MAX_DISPLAY)
		if ((is_display(count)) == 1)
			return (1);
	print_line();
	if ((maxlen = get_max_len(match) + 1) > get_cols_term())
		return (0);
	cols = get_columns_display(count, maxlen);
	if ((rows = get_rows_display(count, cols)) == 1 && count <= MAX_DISPLAY)
		print_line();
	tmp = match;
	while (tmp->prev)
		tmp = tmp->prev;
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
	return (0);
}

int			lst_match_more_than_to_find(t_auto_comp *match, unsigned int len)
{
	int				ret;
	int				len_to_find;
	t_auto_comp		*curr;

	ret = 0;
	len_to_find = 0;

	while (match->prev)
		match = match->prev;
	curr = match;
	ret = len;
/*	
	ft_printf("match->name |%s|, len |%d|", match->name, len);
	sleep(1);
	*/
	
	if (ret > 0)
		ret--;
	
	while (curr->name && curr->name[ret] && curr->next)
	{
		/*
	ft_printf("curr->name |%s|", curr->next->name);
	sleep(1);
	*/
		curr = curr->next;
		if (curr->name[ret]	!= match->name[ret])
			return (ret - len);
		if (!curr->next)
		{
			curr = match;
			ret++;
		}
	}
	return (ret - len_to_find - 1);
}

char		*get_ret_or_display_matches(t_auto_comp *match, char *to_find, unsigned int len)
{
	int				diff_len;
	char			*ret_str;
	int				is_empty_last_c;

//	ft_list_sort_ascii(match); //TODO
	ret_str = NULL;
	is_empty_last_c = 0;

	while (match->prev)
		match = match->prev;
/*	
	ft_printf("|%s|", match->name);
	sleep(2);
*/
	if (len_lst(match) == 1)//one only match 
		ret_str = ft_strdup(match->name);
	else if ((diff_len = lst_match_more_than_to_find(match, len)))//if all matches have a common pattern longer than to_find : diff_len = nb of char to add
	{
		if (match->name[diff_len] && (match->name[diff_len] == ' ' || match->name[diff_len] == '/'))
			is_empty_last_c = 1;
		ft_putnbr(diff_len);
		sleep(1);
		if (!(ret_str = ft_strndup(match->name, len + diff_len - is_empty_last_c)))
			ERROR_MEM
	}
	else//display list of matches et ret_str est une copy de to_find car input pas modifie
	{
		display_various(match);
		if (to_find)
			ret_str = ft_strdup(to_find);
	}
	del_match(match);
	return (ret_str);
	
}
