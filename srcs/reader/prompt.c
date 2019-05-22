#include "libterm.h"
#include "input.h"

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
		vars->cmd_value = 0;
		ft_memdel((void*)&zsh);
	}
}
