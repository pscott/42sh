#include "history.h"

/*
**	Switches the content of the current st_cmd, updating it with the newcmd
**	string. Cuts the trailing \n in the process, making sure that the string
**	copied does not end with a newline characters.
**	Makes sure to free the previous string before updating.
*/

static void	switch_st_cmd(t_st_cmd *st_cmd, char *newcmd)
{
	size_t		len;
	t_st_txt	*st_txt;
	char		*trunc_newcmd;

	if ((len = ft_strlen(newcmd)) > 0)
	{
		if (newcmd[len - 1] == '\n')
			len--;
	}
	if (!(trunc_newcmd = ft_strndup(newcmd, len)))
		ERROR_MEM;
	st_txt = st_cmd->st_txt;
	go_to_start(st_cmd);
	reposition_cursor(st_cmd);
	execute_str(CLEAR_BELOW);
	init_relative_pos(st_cmd);
	//free st_txt
	st_cmd->st_txt = init_st_txt(trunc_newcmd);
	write_st_cmd(st_cmd);
	st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;;
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	ft_memdel((void*)&trunc_newcmd);
}

/*
**	Gets the previous history in the hist_list, and calls switch_st_cmd,
**	switching the characters displayed on screen to those of the previous
**	history.
*/

void	get_previous_history(t_st_cmd *st_cmd)
{
	if (!st_cmd->hist_lst || !st_cmd->hist_lst->prev)
		ft_putstr(BELL);
	else if (st_cmd->hist_lst->prev)
	{
		free(st_cmd->hist_lst->cpy);
		if (!(st_cmd->hist_lst->cpy = ft_strdup(st_cmd->st_txt->txt))) //protect
			ERROR_MEM;
		st_cmd->hist_lst = st_cmd->hist_lst->prev;
		switch_st_cmd(st_cmd, st_cmd->hist_lst->cpy);
	}
}

/*
**	Gets the next history in the hist_list, and calls switch_st_cmd, switching
**	the characters displayed on screen to those of the next history.
*/


void	get_next_history(t_st_cmd *st_cmd)
{
	if (!st_cmd->hist_lst || !st_cmd->hist_lst->next)
		ft_putstr(BELL);
	else
	{
		free(st_cmd->hist_lst->cpy);
		if (!(st_cmd->hist_lst->cpy = ft_strdup(st_cmd->st_txt->txt))) //protect
			ERROR_MEM;
		st_cmd->hist_lst = st_cmd->hist_lst->next;
		switch_st_cmd(st_cmd, st_cmd->hist_lst->cpy);
	}
}
