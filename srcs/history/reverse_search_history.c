#include "input.h"
#include "signals.h"
#include "history.h"
#include "line_editing.h"
#include "builtins.h"
#include "libft.h"

int					strstr_adapted(const char *haystack, const char *needle)
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


int					search_reverse_in_histo(t_st_cmd **st_cmd, char *to_find)
{
	if ((*st_cmd)->hist_lst->next == NULL)
		(*st_cmd)->hist_lst = (*st_cmd)->hist_lst->prev;
	while ((*st_cmd)->hist_lst)
	{
		if (strstr_adapted((*st_cmd)->hist_lst->txt, to_find) == 1)
		{
			if (!((*st_cmd)->st_txt->txt = ft_strndup((*st_cmd)->hist_lst->txt, ft_strlen((*st_cmd)->hist_lst->txt) - 1)))
				ERROR_MEM;
			(*st_cmd)->st_txt->data_size = ft_strlen((*st_cmd)->st_txt->txt);
			(*st_cmd)->st_txt->tracker = ft_strlen((*st_cmd)->st_txt->txt) - ft_strlen(ft_strrstr((*st_cmd)->st_txt->txt, to_find));
			return (0);
		}
		if ((*st_cmd)->hist_lst->prev)
			(*st_cmd)->hist_lst = (*st_cmd)->hist_lst->prev;
		else
			break ;
	}
	return (1);

}

int			ft_isprint_ctrlr(char buf[64])
{
	char			c;

	if (ft_strlen(buf) == 1)
	{
		c = buf[0];
		if ((c > 31 && c < 127) || c == ' ' )
			return (1);
	}
	else if (!ft_strncmp(buf, CTRL_R, CTRL_R_LEN))
		return (1);
	return (0);
}

int		switch_and_return(const char buf[64], t_st_cmd *st_cmd)
{
	char *newcmd;

	if (ft_strncmp(buf, CTRL_C, CTRL_C_LEN) == 0) // care to + 1 because of "\x03a"
	{
		if (!(st_cmd->st_txt->txt[0]))
			st_cmd->st_txt->txt[0] = ' ';
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		reposition_cursor(st_cmd);
		write(1, "^C\n", 3);
		return (ctrl_c_case);
	}
	free_st_prompt(&st_cmd->st_prompt);
	st_cmd->st_prompt = init_st_prompt(NULL);
	if (ft_strncmp(buf, "\r", 2)  == 0 || ft_strncmp(buf, "\n", 2) == 0)
		newcmd = ft_strjoin(st_cmd->st_txt->txt, "\n"); // protect
	else
		newcmd = ft_strdup(st_cmd->st_txt->txt); // protect
	move_cursor(st_cmd->start_pos.col, st_cmd->start_pos.row);
	ft_printf("%s", st_cmd->st_prompt->prompt);
	switch_st_cmd(st_cmd, newcmd);
	free(newcmd);
	if (ft_strncmp(buf, "\r", 2)  == 0 || ft_strncmp(buf, "\n", 2) == 0)
	{
		if (!(st_cmd->st_txt->txt[0]))
			st_cmd->st_txt->txt[0] = ' ';
		write(1, "\n", 1);
		return (enter_case);
	}
	else
	{
		return (quit_case);
	}
}

static int	init_vars(size_t *malloc_size, int *prompt_type, char **stock, char buf[64])
{
	*malloc_size = 256;
	*prompt_type = 0;
	if (!(*stock = ft_strnew(*malloc_size + 1)))
		ERROR_MEM;
	ft_bzero((void *)buf, 64);
	return (0);
}

/*
**	If buf_received == ctrlr, reverse-i-search in historic
**	Returns 0 if the key is not ctrlr 
**	Returns 1 if it is ctrlr + display new prompt + search
*/

int		handle_reverse_search_history(t_st_cmd *st_cmd)
{
	char			*stock;
	char			buf[64];
	int				ret;
	size_t			malloc_size;
	int				prompt_type;

	init_vars(&malloc_size, &prompt_type, &stock, buf);
	print_prompt_search_histo(st_cmd, stock, prompt_type);
	while ((ret = read(STDIN_FILENO, buf, 64)) > 0)
	{
		if (!ft_isprint_ctrlr(buf)) // care buf is 64 bytes long... strncmp only first byte, why not use char c ?
		{
			if (!ft_strncmp(buf, BACKSPACE, BACKSPACE_LEN) && stock[0])
				stock[ft_strlen(stock) - 1] = '\0';
			else
				return (switch_and_return(buf, st_cmd));
		}
		else
		{
			stock = ft_realloc(stock, ft_strlen(stock) - 1, &malloc_size, 1); // ?? buf is 64 bytes long
			stock[ft_strlen(stock)] = buf[0];
		}
		prompt_type = search_reverse_in_histo(&st_cmd, stock);
		print_prompt_search_histo(st_cmd, stock, prompt_type);
		ft_bzero((void *)buf, 64);
	}
	return (0);
}
