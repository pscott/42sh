#include "input.h"
#include "line_editing.h"

void			zsh_newline(t_st_cmd *st_cmd)
{
	size_t	len;
	char	*zsh;

	len = st_cmd->window->ws_col - 1 > 0 ? st_cmd->window->ws_col - 1 : 2;
	if (!(zsh = malloc((size_t)sizeof(*zsh) * len)))
		clean_exit(1, MALLOC_ERR);
	ft_memset(zsh, ' ', len);
	execute_str(HIGHLIGHT);
	write(TERM_FD, "%", 1);
	execute_str(NO_HIGHLIGHT);
	write(TERM_FD, zsh, len);
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
		init_relative_pos(&st_cmd->cursor_pos, st_cmd->window,
			st_cmd->st_prompt->size);
		if (vars->cmd_value)
			ft_dprintf(TERM_FD, "%s", RED);
		else
			ft_dprintf(TERM_FD, "%s", GREEN);
		ft_dprintf(TERM_FD, "%s%s", st_cmd->st_prompt->prompt, FG_DFL);
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
		clean_exit(1, MALLOC_ERR);
	if (!(tmp = ft_strjoin(new_prompt, buf)))
		clean_exit(1, MALLOC_ERR);
	ft_strdel(&new_prompt);
	if (!(new_prompt = ft_strjoin(tmp, "': ")))
		clean_exit(1, MALLOC_ERR);
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
		go_to_prompt_start(st_cmd);
		execute_str(CLEAR_BELOW);
		replace_prompt(st_cmd, buf, prompt_type);
		tmp = st_cmd->st_txt->tracker;
		st_cmd->st_txt->tracker = 0;
		init_relative_pos(&st_cmd->cursor_pos, st_cmd->window,
			st_cmd->st_prompt->size);
		ft_dprintf(TERM_FD, "%s", st_cmd->st_prompt->prompt);
		write_st_cmd(st_cmd);
		st_cmd->st_txt->tracker = tmp;
		reposition_cursor(st_cmd, st_cmd->st_txt->tracker);
	}
}
