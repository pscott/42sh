#include "input.h"
#include "line_editing.h"

static void		print_color(char *str, const char *color)
{
	if (!str)
		return ;
	if (!color)
		ft_dprintf(TERM_FD, "%s", str);
	else
		ft_dprintf(TERM_FD, "%s%s%s", color, str, FG_DFL);
}
void			print_prompt(t_st_cmd *st_cmd, int zsh)
{
	t_vars		*vars;

	vars = get_vars(NULL);
	if (isatty(STDIN_FILENO))
	{
		if (zsh)
			zsh_newline(st_cmd);
		init_relative_pos(&st_cmd->cursor_pos, st_cmd->window,
			st_cmd->st_prompt->size);
		if (ft_strequ(st_cmd->st_prompt->name, STD_PROMPT))
			print_color(st_cmd->st_prompt->name, SHELL_COLOR);
		else
			print_color(st_cmd->st_prompt->name, NULL);
		print_color(st_cmd->st_prompt->dir, DIR_COLOR);
		print_color(st_cmd->st_prompt->exit, STATUS_COLOR);
		print_color(st_cmd->st_prompt->end, NULL);
	}
}

