#include "input.h"
#include "libft.h"
#include "line_editing.h"
#include "history.h"

int			print_prompt_search_history(t_st_cmd *st_cmd)
{
	t_vars	*vars;

	vars = get_vars(NULL);
	move_cursor(st_cmd->start_pos.col, st_cmd->start_pos.row);
	ft_dprintf(OUTPUT_FD, "%s%s%s", vars->cmd_value ? RED : GREEN,
			st_cmd->st_prompt->prompt, FG_DFL);
	return (0);
}
