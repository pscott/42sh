#include "line_editing.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>

/*
**	Updates the window struct passed as a parameter by calling the ioctl
**	function. Exits if it fails.
*/

void			init_relative_pos(t_pos *cursor_pos, struct winsize *window,
	size_t prompt_size)
{
	if (!window)
		return ;
	if (!window->ws_col)
	{
		cursor_pos->col = prompt_size;
		cursor_pos->row = prompt_size;
	}
	else if (window->ws_col > 0)
	{
		cursor_pos->col = prompt_size % window->ws_col;
		cursor_pos->row = prompt_size / window->ws_col;
	}
}

void			update_window_struct(struct winsize *window)
{
	if (isatty(TERM_FD) == 0)
		return ;
	ioctl(STDIN_FILENO, TIOCGWINSZ, window);
	window->ws_col = ft_max(window->ws_col, 0);
	window->ws_row = ft_max(window->ws_col, 0);
}

/*
**	Allocates and updates a fresh window struct, containing information about
**	the window size.
*/

struct winsize	*init_window_struct(void)
{
	struct winsize	*window;

	if (!(window = malloc(sizeof(*window))))
		clean_exit(1, 1);
	update_window_struct(window);
	return (window);
}
