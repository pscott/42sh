#include "input.h"
#include "signals.h"
#include "history.h"
#include "line_editing.h"
#include "builtins.h"
#include "libft.h"

/*
**	Returns 1 if ctrld is pressed and line is empty
**	Returns 0 if the key is not ctrld
**	Returns -1 if ctrld is pressed but line is not empty
*/

int		check_for_quit(t_st_cmd *st_cmd, const char *buf)
{
	if (ft_strncmp(buf, CTRL_D, 2) == 0)
	{
		if (st_cmd->st_txt->data_size == 0)
		{
			if (st_cmd->prev)
				ft_dprintf(STDERR_FILENO, "42sh: unexpected EOF\n");
			*st_cmd->st_txt->txt = 0;
			return (1);
		}
		else if (st_cmd->st_txt->tracker >= st_cmd->st_txt->data_size)
			return (-1);
		else
			delete_right(st_cmd);
		return (-1);
	}
	else
		return (0);
}

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
				ERROR_MEM
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

int		check_case(const char buf[64])
{
	if (!ft_strncmp(buf, "\r", 1))
		return (enter_case);
	else if (!ft_strncmp(buf, CTRL_C, CTRL_C_LEN))
		return (ctrl_c_case);
	else
		return (quit_case);
}

int		handle_quit(t_st_cmd *st_cmd, const char buf[64])
{
	/*
	free_st_prompt(&st_cmd->st_prompt);
	st_cmd->st_prompt = init_st_prompt(NULL);	
	execute_str(BEGIN_LINE);
	execute_str(CLEAR_BELOW);
	print_prompt(st_cmd);
	st_cmd->st_txt->tracker = 0;
	write_st_cmd(st_cmd);
	*/
	return (check_case(buf));
}

/*
**	If buf_received == ctrlr, reverse-i-search in historic
**	Returns 0 if the key is not ctrlr 
**	Returns 1 if it is ctrlr + display new prompt + search
*/

int		check_for_search_histo(t_st_cmd *st_cmd, const char *buf_received)
{
	char			*stock;
	char			buf[64];
	int				ret;
	size_t			i;
	t_st_cmd		*to_find;
	size_t			malloc_size;
	int				prompt_type;

	to_find = NULL;
	i = 0;
	malloc_size = 256;
	prompt_type = 0;
	if (ft_strncmp(buf_received, CTRL_R , 2) == 0)
	{
		if (!(stock = ft_strnew(malloc_size + 1)))
			ERROR_MEM
		ft_bzero((void *)stock, malloc_size + 1);
		ft_bzero((void *)buf, 64);
		print_prompt_search_histo(st_cmd, stock, prompt_type);
		while ((ret = read(STDIN_FILENO, buf, 64)) > 0)
		{
			if (!ft_isprint_ctrlr(buf))
			{
				// 3 cas : ctrlc -> affiche ctrlc, nouveau prompt une ligne en dessous, entree -> substitue par un prompt regular le prompt de recherche et execute, char de merdre -> overwrite un prompt sur la meme ligne
				if (!ft_strncmp(buf, BACKSPACE, BACKSPACE_LEN) && stock[0])
					stock[ft_strlen(stock) - 1] = '\0';
				else
				{
					ft_strdel(&stock);
					return (handle_quit(st_cmd, buf));
				}
			}
			else
			{
				stock = ft_realloc(stock, ft_strlen(stock) - 1, &malloc_size, 1);
				stock[ft_strlen(stock)] = buf[0];
			}
				execute_str(BEGIN_LINE);
				execute_str(CLEAR_BELOW);
				prompt_type = search_reverse_in_histo(&st_cmd, stock);
				print_prompt_search_histo(st_cmd, stock, prompt_type);
				ft_bzero((void *)buf, 64);
		}
		return (1);
	}
	else
	{
		return (0);
	}
}
