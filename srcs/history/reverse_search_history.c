#include "input.h"
#include "history.h"

int				strstr_adapted(const char *haystack, const char *needle)
{
	size_t			i;
	size_t			j;

	if (*needle == 0)
		return (0);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j] && needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == 0)
			return (1);
		i = i - j + 1;
	}
	return (0);
}

/*
**	Looking for pattern "to_find" in st_cmd->hist_lst, recursively
**	Returns 0 if to_find is not found
**	Returns 1 if to_find is found
*/

int				search_reverse_in_histo(t_st_cmd **st_cmd, char *to_find)
{
	if ((*st_cmd)->hist_lst->next == NULL)
		(*st_cmd)->hist_lst = (*st_cmd)->hist_lst->prev;
	while ((*st_cmd)->hist_lst)
	{
		if (strstr_adapted((*st_cmd)->hist_lst->txt, to_find) == 1)
		{
			if (!((*st_cmd)->st_txt->txt = ft_strndup((*st_cmd)->hist_lst->txt,
							ft_strlen((*st_cmd)->hist_lst->txt) - 1)))
				ERROR_MEM;
			(*st_cmd)->st_txt->data_size = ft_strlen((*st_cmd)->st_txt->txt);
			(*st_cmd)->st_txt->tracker = ft_strlen((*st_cmd)->st_txt->txt) -
				ft_strlen(ft_strrstr((*st_cmd)->st_txt->txt, to_find));
			return (0);
		}
		if ((*st_cmd)->hist_lst->prev)
			(*st_cmd)->hist_lst = (*st_cmd)->hist_lst->prev;
		else
			break ;
	}
	return (1);
}

static int		init_vars(size_t *malloc_size, int *prompt_type, char **stock)
{
	*malloc_size = 256;
	*prompt_type = 0;
	if (!(*stock = ft_strnew(*malloc_size + 1)))
		ERROR_MEM;
	return (0);
}

static	void	realloc_stock(char **stock, char buf, size_t malloc_size)
{
	(*stock) = ft_realloc((*stock), ft_strlen((*stock)) - 1, &malloc_size, 1);
	(*stock)[ft_strlen((*stock))] = buf;
}

static int		is_quit_char(char buf)
{
	if (buf != 18 && buf != '\x7f' && buf != ' '
		&& ft_isprint(buf) == 0)
		return (1);
	return (0);
}

/*
**	If buf_received == ctrlr, reverse-i-search in historic
**	Returns 0 if the key is not ctrlr
**	Returns 1 if it is ctrlr + display new prompt + search
*/

int				handle_reverse_search_history(t_st_cmd *st_cmd,
		size_t malloc_size, int prompt_type)
{
	char			*stock;
	char			buf;
	int				ret;
	char			escape[BUF_SIZE + 1];

	init_vars(&malloc_size, &prompt_type, &stock);
	print_prompt_search_histo(st_cmd, stock, prompt_type);
	ft_bzero(escape, sizeof(escape));
	while ((ret = read(STDIN_FILENO, &buf, 1)) > 0)
	{
		escape[ft_strlen(escape)] = buf;
		if (is_valid_escape(escape) == 0)
			continue ;
		buf = escape[0];
		if (buf != 18)
		{
			if (ft_strlen(escape) > 1 || is_quit_char(buf))
			{
				if (buf == '\x7f' && stock[0])
					stock[ft_strlen(stock) - 1] = '\0';
				else if (buf != '\x7f')
				{
					ft_strdel(&stock);
					return (switch_and_return(buf, st_cmd));
				}
			}
			else
				realloc_stock(&stock, buf, malloc_size);
			prompt_type = search_reverse_in_histo(&st_cmd, stock);
			print_prompt_search_histo(st_cmd, stock, prompt_type);
		}
		ft_bzero(escape, sizeof(escape));
	}
	return (0);
}
