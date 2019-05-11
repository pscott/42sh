#include "libft.h"
#include "line_editing.h"

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

static char	*get_unique_match(t_auto_comp *match, char *to_find, unsigned int len)
{
	int				to_find_len;
	char			*ret_str;
	int				i;
	t_auto_comp		*s_tmp;

//	ft_printf("\n%s\n", to_find);
//	to_find_len = ft_strlen(to_find);
	if (!to_find[len - 1] || is_white_spaces(to_find[len - 1]))//si !cursor_pos->next, alors curseur en fin de ligne, et si isspace cursor_pos->next, alors un espace apres le curseur : il faut donc join un espace a match->name. dans tous les cas ret est malloc
		ret_str = ft_strjoin(match->name, " ");
	else//auto_completion au milieu d'un mot
		ret_str = ft_strdup(match->name);
/*	while (tmp[to_find_len + i]) PLUS BESOIN de stock input directement
	{
		stock_input(tmp[to_find_len + i]);
		i++;
	}*/
//	display_input();  PLUS BESOIN de display ici
//	ft_strdel(&tmp); ON NE free plus ici du coup
	return (ret_str);
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
	ft_printf("\nDisplay all %d possibilities? (y or n)", count);		
	while (1)
	{
		read(0, &c, 1);
		if (c == 'n' || c == 'N' || c == 127)
		{
//			signal_setup();
		//	if (c == backspace)
			/*	free_input(&(g_sh.input), &(g_sh.input_len));
				g_sh.cursor_pos = NULL;*/
		//		ft_putchar('\n');
		//		write_prompt(0);
//			if (!ft_strncmp(buf, KEY_BACKSPACE, 1))
//				display_input();
			return (1);
		}
		else if (c == 'y' || c == 'Y' || c == 32)
		{
//			signal_setup();
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

static int	display_various(t_auto_comp *match, char *to_find)
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
	ft_putchar('\n');//down_line
	if ((maxlen = get_max_len(match) + 1) > get_cols_term())
		return (0);
	cols = get_columns_display(count, maxlen);
	if ((rows = get_rows_display(count, cols)) == 1 && count <= MAX_DISPLAY)
		ft_putchar('\n');
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
	ft_putchar('\n');// down_line
	}
/*	write_prompt(0);
	g_sh.cursor_pos = g_sh.input;
	display_input();
	put_cursor_end_line();*/// a faire a la fin de la boucle auto complete
	return (0);
}

int			lst_match_more_than_to_find(t_auto_comp *match, char *to_find)
{
	int				ret;
	int				len_to_find;
	t_auto_comp		*curr;

	ret = 0;

	while (match->prev)
		match = match->prev;
	curr = match->next;
	len_to_find = ft_strlen(to_find - 2);
	ret = len_to_find;
	while (curr->name[ret] && curr->next)
	{
		if (curr->name[ret]	!= match->name[ret])
			return (ret - len_to_find);
		curr = curr->next;
		if (!curr->next)
		{
			curr = match->next;
			ret++;
		}
	}
	return (ret - len_to_find);
}

char		*get_ret_or_display_matches(t_auto_comp *match, char *to_find, unsigned int len)
{
	int				ret;
	int				diff_len;
	char			*ret_str;

	ft_list_sort_ascii(match);
	ret_str = NULL;
	if (len_lst(match) == 1)//one only match 
	{
		ret_str = get_unique_match(match, to_find, len);//return match->name append d'un espace ou non selon milieu ou fin de mot
	}
	else if ((diff_len = lst_match_more_than_to_find(match, to_find)))//if all matches have a common pattern longer than to_find : diff_len = nb of char to add
	{
		if (!(ret_str = ft_strndup(match->name, ft_strlen(to_find - 2) + diff_len)))
			return (NULL);
			//error_exit(ERR_MALLOC);
	}
	else//display list of matches et ret_str est une copy de to_find car input pas modifie
	{
		display_various(match, to_find);

		ret_str = ft_strdup(to_find);
	}
	del_match(match);
	return (ret_str);
	
}
