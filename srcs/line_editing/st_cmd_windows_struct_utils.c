#include "line_editing.h"
#include <sys/ioctl.h>
#include "history.h"
#include "ast.h"

/*
**	Updates the window struct passed as a parameter by calling the ioctl
**	function. Exits if it fails.
*/

void			init_relative_pos(t_st_cmd *st_cmd)
{
	if (isatty(STDIN_FILENO) == 0)
		return ;
	st_cmd->relative_pos.col = st_cmd->st_prompt->size % st_cmd->window->ws_col;
	st_cmd->relative_pos.row = st_cmd->st_prompt->size / st_cmd->window->ws_col;
}

void			update_window_struct(struct winsize *window)
{
	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, window) == -1)
	{
		ft_dprintf(2, "error ioctl: exiting!\n");
		clean_exit(1);
	}
}

/*
**	Allocates and updates a fresh window struct, containing information about
**	the window size.
*/

struct winsize	*init_window_struct(void)
{
	struct winsize	*window;

	if (!(window = malloc(sizeof(*window))))
		ERROR_MEM;
	update_window_struct(window);
	return (window);
}
