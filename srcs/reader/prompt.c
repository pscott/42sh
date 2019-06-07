#include "input.h"
#include "line_editing.h"

static void		update_prompt_pos(t_st_cmd *st_cmd)
{
	int times;

	times = st_cmd->st_prompt->size / st_cmd->window->ws_col;
	while (times)
	{
		update_start_pos(st_cmd);
		execute_str(SCROLL_DOWN);
		times--;
	}
}

static void		zsh_newline(t_st_cmd *st_cmd)
{
	int		len;
	char	*zsh;

	len = st_cmd->window->ws_col - 1 > 0 ? st_cmd->window->ws_col - 1 : 2;
	if (!(zsh = malloc(sizeof(*zsh) * len)))
		clean_exit(1, 1);
	ft_memset(zsh, ' ', len);
	execute_str(HIGHLIGHT);
	write(1, "%", 1);
	execute_str(NO_HIGHLIGHT);
	write(1, zsh, len);
	execute_str(BEGIN_LINE);
	execute_str(ERASE_ENDLINE);
	ft_memdel((void*)&zsh);
}
void			print_prompt(t_st_cmd *st_cmd)
{
	t_vars		*vars;

	vars = get_vars(NULL);
	if (isatty(STDIN_FILENO))
	{
		zsh_newline(st_cmd);
		retrieve_pos(&st_cmd->start_pos);
		if (vars->cmd_value)
			ft_printf("%s", RED);
		else
			ft_printf("%s", GREEN);
		ft_printf("%s%s", st_cmd->st_prompt->prompt, FG_DFL);
		update_prompt_pos(st_cmd);
		get_pos(st_cmd, 0);
		reposition_cursor(st_cmd);
	}
}

static void		replace_prompt(t_st_cmd *st_cmd, const char *buf,
		int prompt_type)
{
	char		*new_prompt;
	char		*tmp;

	free_st_prompt(&st_cmd->st_prompt);
	if (prompt_type == 0)
		new_prompt = ft_strjoin(PROMPT_REVERSE_I_SEARCH_SUCC, "`");
	else
		new_prompt = ft_strjoin(PROMPT_REVERSE_I_SEARCH_FAIL, "`");
	if (!new_prompt)
		clean_exit(1, 1);
	if (!(tmp = ft_strjoin(new_prompt, buf)))
		clean_exit(1, 1);
	ft_strdel(&new_prompt);
	if (!(new_prompt = ft_strjoin(tmp, "': ")))
		clean_exit(1, 1);
	ft_strdel(&tmp);
	st_cmd->st_prompt = init_st_prompt(new_prompt);
	st_cmd->st_prompt->size = ft_strlen(st_cmd->st_prompt->prompt);
	ft_strdel(&new_prompt);
}

void			print_prompt_search_histo(t_st_cmd *st_cmd, const char *buf,
		int prompt_type)
{
	size_t		tmp;

	if (isatty(STDIN_FILENO))
	{
		replace_prompt(st_cmd, buf, prompt_type);
		move_cursor(st_cmd->start_pos.col, st_cmd->start_pos.row);
		tmp = st_cmd->st_txt->tracker;
		st_cmd->st_txt->tracker = 0;
		init_relative_pos(st_cmd);
		ft_printf("%s", st_cmd->st_prompt->prompt);
		write_st_cmd(st_cmd);
		st_cmd->st_txt->tracker = tmp;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		reposition_cursor(st_cmd);
	}
}
