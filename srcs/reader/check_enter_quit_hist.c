#include "history.h"
#include "line_editing.h"

/*
**	Returns 1 if ctrld is pressed and line is empty
**	Returns 0 if the key is not ctrld
**	Returns -1 if ctrld is pressed but line is not empty
*/

int		check_for_quit(t_st_cmd *st_cmd, const char *buf)
{
	if (ft_strncmp(buf, CTRL_D, 2) == 0)
	{
		if (st_cmd->st_txt->data_size == 0)
		{
			if (st_cmd->prev)
				ft_dprintf(STDERR_FILENO, "42sh: unexpected EOF\n");
			*st_cmd->st_txt->txt = 0;
			return (1);
		}
		else if (st_cmd->st_txt->tracker >= st_cmd->st_txt->data_size)
			return (-1);
		else
			delete_right(st_cmd);
		return (-1);
	}
	else
		return (0);
}

/*
**	If buf_received == ctrlr, reverse-i-search in historic
**	Returns 0 if the key is not ctrlr
**	Returns > 0 if ctrlr pressed, depending of the state of the way our reading
**		loop is broken
*/

int		check_for_search_histo(t_st_cmd *st_cmd, const char *buf_received,
	int mode)
{
	if (ft_strncmp(buf_received, CTRL_R, 2) == 0)
	{
		if (isatty(TERM_FD) == 0)
			return (1);
		else
			return (handle_reverse_search_history(st_cmd, 0, 0, mode));
	}
	else
		return (0);
}

int		check_for_enter(const char *buf)
{
	if (ft_strncmp(buf, "\r", 2) == 0 || ft_strncmp(buf, "\n", 2) == 0)
		return (1);
	else
		return (0);
}
