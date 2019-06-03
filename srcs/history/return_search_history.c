#include "input.h"
#include "libft.h"
#include "line_editing.h"
#include "history.h"

static int	interrupt_search(t_st_cmd *st_cmd)
{
	if (!(st_cmd->st_txt->txt[0]))
		st_cmd->st_txt->txt[0] = ' ';
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
	write(STDERR_FILENO, "^C", 2);
	execute_str(PRINT_LINE);
	return (ctrl_c_case);
}

int			switch_and_return(char buf, t_st_cmd *st_cmd)
{
	char *newcmd;

	if (buf == 3)
		return (interrupt_search(st_cmd));
	free_st_prompt(&st_cmd->st_prompt);
	st_cmd->st_prompt = init_st_prompt(NULL);
	if (buf == '\r' || buf == '\n')
		newcmd = ft_strjoin(st_cmd->st_txt->txt, "\n");
	else
		newcmd = ft_strdup(st_cmd->st_txt->txt);
	if (!newcmd)
		ERROR_MEM;
	move_cursor(st_cmd->start_pos.col, st_cmd->start_pos.row);
	ft_printf("%s", st_cmd->st_prompt->prompt);
	switch_st_cmd(st_cmd, newcmd);
	free(newcmd);
	if (buf == '\r'|| buf == '\n')
	{
		if (!(st_cmd->st_txt->txt[0]))
			st_cmd->st_txt->txt[0] = ' ';
		st_cmd->st_txt->txt = ft_realloc(st_cmd->st_txt->txt, st_cmd->st_txt->data_size, &st_cmd->st_txt->malloc_size, 1);
		st_cmd->st_txt->txt[st_cmd->st_txt->data_size] = '\n';
		execute_str(PRINT_LINE);
		return (enter_case);
	}
	else
		return (quit_case);
}
