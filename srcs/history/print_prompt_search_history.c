#include "input.h"
#include "libft.h"
#include "line_editing.h"
#include "history.h"

int			print_prompt_search_history(t_st_cmd *st_cmd)
{
	t_vars	*vars;

	vars = get_vars(NULL);
	go_to_prompt_start(st_cmd);
	ft_dprintf(TERM_FD, "%s%s%s", vars->cmd_value ? RED : GREEN,
			st_cmd->st_prompt->prompt, FG_DFL);
	return (0);
}
