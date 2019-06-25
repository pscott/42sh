#include "history.h"
#include "line_editing.h"

/*
**	Switches the content of the current st_cmd, updating it with the newcmd
**	string. Cuts the trailing \n in the process, making sure that the string
**	copied does not end with a newline characters.
**	Makes sure to free the previous string before updating.
*/

void	switch_st_cmd(t_st_cmd *st_cmd, char *newcmd)
{
	size_t		len;
	char		*trunc_newcmd;

	if ((len = ft_strlen(newcmd)) > 0)
	{
		if (newcmd[len - 1] == '\n')
			len--;
	}
	if (!(trunc_newcmd = ft_strndup(newcmd, len)))
		clean_exit(1, 1);
	go_to_prompt_start(st_cmd);
	execute_str(CLEAR_BELOW);
	free_st_txt(&st_cmd->st_txt);
	st_cmd->st_txt = init_st_txt(trunc_newcmd);
	init_relative_pos(&st_cmd->cursor_pos, st_cmd->window,
		st_cmd->st_prompt->size);
	print_prompt(st_cmd, 0); // ?
	write_st_cmd(st_cmd);
	st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
	reposition_cursor(st_cmd, st_cmd->st_txt->tracker);
	ft_memdel((void*)&trunc_newcmd);
}

/*
**	Gets the previous history in the hist_list, and calls switch_st_cmd,
**	switching the characters displayed on screen to those of the previous
**	history.
*/

void	get_previous_history(t_st_cmd *st_cmd)
{
	if (isatty(TERM_FD) == 0)
		return ;
	if (!st_cmd->hist_lst || !st_cmd->hist_lst->prev)
		write(STDIN_FILENO, BELL, 1);
	else if (st_cmd->hist_lst->prev)
	{
		free(st_cmd->hist_lst->cpy);
		if (!(st_cmd->hist_lst->cpy = ft_strdup(st_cmd->st_txt->txt)))
			clean_exit(1, 1);
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
	if (isatty(TERM_FD) == 0)
		return ;
	if (!st_cmd->hist_lst || !st_cmd->hist_lst->next)
		write(STDIN_FILENO, BELL, 1);
	else
	{
		free(st_cmd->hist_lst->cpy);
		if (!(st_cmd->hist_lst->cpy = ft_strdup(st_cmd->st_txt->txt)))
			clean_exit(1, 1);
		st_cmd->hist_lst = st_cmd->hist_lst->next;
		switch_st_cmd(st_cmd, st_cmd->hist_lst->cpy);
	}
}
