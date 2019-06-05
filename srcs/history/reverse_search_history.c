#include "input.h"
#include "signals.h"
#include "history.h"
#include "line_editing.h"
#include "builtins.h"
#include "libft.h"

/*
**	Looking for pattern "to_find" in st_cmd->hist_lst, reversely.
**	First, if our st_txt is not empty (ie we already had a successful search
**		or something was written when ctrl r was actived), we look for
**		our pattern between the beginning of st_txt and our tracker.
**	Then, if we did not find any match, we look for our pattern in
**		previous history entries.
**	Returns 0 if to_find is not found
**	Returns 1 if to_find is found
*/

int				search_reverse_in_histo(t_st_cmd **st_cmd, char *to_find, char buf, int prompt_type)
{
	if ((*st_cmd)->st_txt->txt != NULL)
	{
		if (to_find && to_find[0] && ft_strrnstr((*st_cmd)->st_txt->txt, to_find, (*st_cmd)->st_txt->tracker))
		{
			(*st_cmd)->st_txt->tracker = ft_strlen((*st_cmd)->st_txt->txt) -
				ft_strlen(ft_strrnstr((*st_cmd)->st_txt->txt, to_find, (*st_cmd)->st_txt->tracker));
			return (0);
		}
		if (((*st_cmd)->hist_lst) && (*st_cmd)->hist_lst->prev)
			(*st_cmd)->hist_lst = (*st_cmd)->hist_lst->prev;
	}
	while ((*st_cmd)->hist_lst)
	{
		if (to_find && to_find[0] && strstr_adapted((*st_cmd)->hist_lst->txt, to_find))
		{
			ft_strdel(&(*st_cmd)->st_txt->txt);
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

int				search_reverse_ctrl_again(t_st_cmd **st_cmd, char *to_find, char buf, int prompt_type)
{

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

	init_vars_reverse_search_histo(&malloc_size, &prompt_type, &stock);
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
			if (buf == '\x7f' && !stock[0])
				prompt_type = 1;
			else
				prompt_type = search_reverse_in_histo(&st_cmd, stock, buf, prompt_type);
			print_prompt_search_histo(st_cmd, stock, prompt_type);
		}
		else if (buf == 18)
		{
			prompt_type = search_reverse_ctrlr_again(&st_cmd, stock);
			print_prompt_search_histo(st_cmd, stock, prompt_type);
		}
		ft_bzero(escape, sizeof(escape));
	}
	return (0);
}
