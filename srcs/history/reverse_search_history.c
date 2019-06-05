#include "input.h"
#include "history.h"

static int		search_in_current_entry(t_st_cmd **st_cmd, char *to_find, size_t tracker)
{
	if ((*st_cmd)->st_txt->txt != NULL && (*st_cmd)->st_txt->txt[0] != '\0')
	{
		if (to_find && to_find[0] && ft_strrnstr((*st_cmd)->st_txt->txt, to_find, tracker))
		{
			(*st_cmd)->st_txt->tracker = ft_strlen((*st_cmd)->st_txt->txt) -
				ft_strlen(ft_strrnstr((*st_cmd)->st_txt->txt, to_find, tracker));
			return (1);
		}
	}
	return (0);
}

static int		search_in_previous_entries(t_st_cmd **st_cmd, char *to_find)
{
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

/*
**	Looking for pattern "to_find" in st_cmd->hist_lst, reversely.
**	First, if our st_txt is not empty (i.e we already had a successful search
**		or something was written when ctrl r was activated), we look for
**		our pattern between the beginning of st_txt and our tracker.
**	Then, if we did not find any match, we look for our pattern in
**		previous history entries.
**	The condition (tracker >= 0) is needed to protect from segmentation
**		fault in case of various ctrl R : in this case, we first need to look
**		for 'to_find' pattern between the beginning of st_txt and tracker - 1..
**	Returns 1 if to_find is found
**	Returns 0 if to_find is not found
*/

int				search_reverse_in_histo(t_st_cmd **st_cmd, char *to_find, int tracker, char buf)
{
	int			ret;
	size_t		tracker_save;
	t_st_txt	*txt_save;


	tracker_save = (*st_cmd)->st_txt->tracker;
	txt_save = (*st_cmd)->st_txt;
	if (buf == 18)
	{
		if ((*st_cmd)->st_txt->txt && ((*st_cmd)->st_txt->txt[0] == '\0'))
			return (-1);
		tracker--;
	}
	if (tracker >= 0)
	{
		if (search_in_current_entry(st_cmd, to_find, tracker))
		{
			return (0);
		}
	}
	if (((*st_cmd)->hist_lst) && (*st_cmd)->hist_lst->prev)
			(*st_cmd)->hist_lst = (*st_cmd)->hist_lst->prev;
			
	ret = search_in_previous_entries(st_cmd, to_find);
	return (ret);
}

static int	handle_quitting_chars_and_bcksp(char buf, char **stock)
{
	if (buf == '\x7f' && (*stock)[0])
		(*stock)[ft_strlen(*stock) - 1] = '\0';
	else if (buf != '\x7f')
	{
		ft_strdel(stock);
		return (1);
	}
	return (0);
}



static int	check_exit_and_realloc(size_t *malloc_size, char buf, char escape[BUF_SIZE + 1], char **stock)
{
	if (buf !=  18 && (ft_strlen(escape) > 1 || is_quit_char(buf)))
	{
		if (handle_quitting_chars_and_bcksp(buf, stock))
			return (1);
	}
	else if (buf != 18)
		realloc_stock(stock, buf, malloc_size);
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
	int				type_save;
	char			escape[BUF_SIZE + 1];

	init_vars_rsh_and_prompt(st_cmd, &malloc_size, &prompt_type, &stock);
	ft_bzero(escape, sizeof(escape));
	while ((ret = read(STDIN_FILENO, &buf, 1)) > 0)
	{
		escape[ft_strlen(escape)] = buf;
		if (is_valid_escape(escape) == 0)
			continue ;
		buf = escape[0];
		if (check_exit_and_realloc(&malloc_size, buf, escape, &stock))
			return (switch_and_return(buf, st_cmd));
		type_save = prompt_type;
		if (buf == '\x7f' && !stock[0])
			prompt_type = 1;
		else if ((prompt_type = search_reverse_in_histo(&st_cmd, stock, (int)(st_cmd->st_txt->tracker), buf)) == -1)
			prompt_type = type_save;
		print_prompt_search_histo(st_cmd, stock, prompt_type);
		ft_bzero(escape, sizeof(escape));
	}
	return (0);
}
