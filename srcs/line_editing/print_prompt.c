#include "input.h"
#include "line_editing.h"

static void		print_color(char *str, const char *color)
{
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
			print_color(st_cmd->st_prompt->name, GREEN);
		else
			print_color(st_cmd->st_prompt->name, NULL);
		if (st_cmd->st_prompt->dir)
			print_color(st_cmd->st_prompt->dir, BLUE);
		if (st_cmd->st_prompt->exit)
			print_color(st_cmd->st_prompt->exit, RED);
		print_color(st_cmd->st_prompt->end, NULL);
	}
}

