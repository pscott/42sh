#include "libterm.h"
#include "input.h"
#include "line_editing.h"

void	print_prompt(t_st_cmd *st_cmd)
{
	char		*zsh;
	int			len;
	t_vars		*vars;

	vars = get_vars(NULL);
	if (isatty(STDIN_FILENO))
	{
		len = st_cmd->window->ws_col - 1 > 0 ? st_cmd->window->ws_col - 1 : 2;
		if (!(zsh = malloc(sizeof(*zsh) * len)))
			ERROR_MEM;
		ft_memset(zsh, ' ', len);
		execute_str(HIGHLIGHT);
		write(1, "%", 1);
		execute_str(NO_HIGHLIGHT);
		write(1, zsh, len);
		execute_str(BEGIN_LINE);
		execute_str(ERASE_ENDLINE);
		retrieve_pos(&st_cmd->start_pos);
		if (vars->cmd_value)
			ft_printf("%s", RED);
		else
			ft_printf("%s", GREEN);
		ft_printf("%s%s", st_cmd->st_prompt->prompt, FG_DFL);
		ft_memdel((void*)&zsh);
	}
}

void	print_prompt_search_histo(t_st_cmd *st_cmd, const char *buf, int prompt_type)
{
	char		*zsh;
	int			len;

	if (isatty(STDIN_FILENO))
	{
		free_st_prompt(&st_cmd->st_prompt);
		if (prompt_type == 0)
			st_cmd->st_prompt = init_st_prompt(PROMPT_REVERSE_I_SEARCH_SUCC);
		else if (prompt_type == 1)
			st_cmd->st_prompt = init_st_prompt(PROMPT_REVERSE_I_SEARCH_FAIL);
		len = st_cmd->window->ws_col - 1 > 0 ? st_cmd->window->ws_col -1 : 2;
		if (!(zsh = ft_strnew(len)))
			ERROR_MEM
		ft_memset(zsh, ' ', len);
	//	write(1, "%", 1);
//		write(1, zsh, len);
		execute_str(BEGIN_LINE);
		execute_str(ERASE_ENDLINE);
		retrieve_pos(&st_cmd->start_pos);
		ft_printf("%s`%s': %s", st_cmd->st_prompt->prompt, buf, st_cmd->st_txt->txt);//enlever et juste display le prompt
		ft_memdel((void*)&zsh);
	}
}
