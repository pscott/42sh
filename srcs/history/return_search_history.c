#include "input.h"
#include "libft.h"
#include "line_editing.h"
#include "history.h"

static int	interrupt_search(t_st_cmd *st_cmd)
{
	if (!(st_cmd->st_txt->txt[0]))
		st_cmd->st_txt->txt[0] = ' ';
	reposition_cursor(st_cmd, st_cmd->st_txt->tracker);
	ft_putstr_fd("^C", TERM_FD);
	execute_str(MOVE_DOWN);
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	return (ctrl_c_case);
}

static int	case_return_newline(t_st_cmd *st_cmd)
{
	if (!(st_cmd->st_txt->txt[0]))
		st_cmd->st_txt->txt[0] = ' ';
	st_cmd->st_txt->txt = ft_realloc(st_cmd->st_txt->txt,
			st_cmd->st_txt->data_size, &st_cmd->st_txt->malloc_size, 1);
	st_cmd->st_txt->txt[st_cmd->st_txt->data_size] = '\n';
	execute_str(MOVE_DOWN);
	return (enter_case);
}

static int	get_good_case_to_ret(char buf,
	t_st_cmd **st_cmd, char escape[BUF_SIZE + 1])
{
	if (buf == '\r' || buf == '\n')
		return (case_return_newline(*st_cmd));
	else
	{
		if (!ft_strncmp(escape, LEFTARROW, ARROW_LEN + 1))
		{
			if ((*st_cmd)->st_txt->tracker > 0)
				--(*st_cmd)->st_txt->tracker;
		}
		else if (!ft_strncmp(escape, RIGHTARROW, ARROW_LEN + 1))
			++(*st_cmd)->st_txt->tracker;
		else if (!ft_strncmp(escape, DOWNARROW, ARROW_LEN + 1))
		{
			if ((*st_cmd)->hist_lst->next && (*st_cmd)->hist_lst->next->next)
				get_next_history(*st_cmd);
		}
		else if (!ft_strncmp(escape, UPARROW, ARROW_LEN + 1))
		{
			if ((*st_cmd)->hist_lst->prev)
				get_previous_history(*st_cmd);
		}
		return (quit_case);
	}
}

int			switch_and_return(t_st_cmd *st_cmd,
	char buf, char escape[BUF_SIZE + 1], int mode)
{
	char	*newcmd;
	size_t	tmp;
	int		ret;

	ret = get_good_case_to_ret(buf, &st_cmd, escape);
	tmp = st_cmd->st_txt->tracker;
	if (buf == 3)
		return (interrupt_search(st_cmd));
	free_st_prompt(&st_cmd->st_prompt);
	if (mode == regular)
		st_cmd->st_prompt = init_st_prompt(STD_PROMPT, newcmd, 0);
	else if (mode == heredoc)
		st_cmd->st_prompt = init_st_prompt(HEREDOC_PROMPT, NULL, 0);
	else if (mode == continue_read)
		st_cmd->st_prompt = init_st_prompt(CONTINUE_PROMPT, NULL, 0);
	if (buf == '\r' || buf == '\n')
		newcmd = ft_strjoin(st_cmd->st_txt->txt, "\n");
	else
		newcmd = ft_strdup(st_cmd->st_txt->txt);
	if (!newcmd)
		clean_exit(1, MALLOC_ERR);
	switch_st_cmd(st_cmd, newcmd);
	st_cmd->st_txt->tracker = tmp;
	free(newcmd);
	return (ret);
}

int			handle_quitting_chars_and_bcksp(char buf, char **stock)
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
