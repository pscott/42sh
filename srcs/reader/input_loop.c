#include "ftsh.h"
#include "input.h"
#include "libterm.h"
#include "line_editing.h"
#include <limits.h>

void	magic_print(char *buf) // debug
{
	int	i;

	i = 0;
	//execute_str(SAVE_CURSOR);
	//move_cursor(0, 0);
	while (i < BUF_SIZE + 1)
	{
		ft_dprintf(2, "%-4d", buf[i]);
		i++;
	}
	//execute_str(RESTORE_CURSOR);
}

/*
**	Returns -1 if buffer is NOT an escape sequence.
**	Returns 0 if buffer might be an escape sequence.
**	Returns 1 if buffer IS an escape sequence.
*/

static int	is_valid_escape(char *buf)
{
	int		len;
	int		last;

	len = ft_strlen(buf);
	if (len >= BUF_SIZE)
		return (-1);
	last = len > 0 ? len - 1 : 0;
	if (buf[last] == '\x03' || buf[last] == '\x04' || buf[last] == '\x1a')
	{
		*buf = buf[last];
		ft_bzero(&buf[1], BUF_SIZE);
		return (-1);
	}
	last = len > 0 ? len - 1 : 0;
	if (check
	if (ft_strncmp(buf, RIGHT, ARROW_LEN + 1) == 0 || ft_strncmp(buf, LEFT, ARROW_LEN + 1) == 0
		|| ft_strncmp(buf, UP, ARROW_LEN + 1) == 0 || ft_strncmp(buf, DOWN, ARROW_LEN + 1) == 0
		|| ft_strncmp(buf, HOME, HOME_LEN + 1) == 0 || ft_strncmp(buf, END, END_LEN + 1) == 0
		|| ft_strncmp(buf, DEL, DEL_LEN + 1) == 0)
		return (1);
	if (ft_strncmp(buf, RIGHT, len) == 0 || ft_strncmp(buf, LEFT, len) == 0
		|| ft_strncmp(buf, UP, len) == 0 || ft_strncmp(buf, DOWN, len) == 0
		|| ft_strncmp(buf, DEL, len) == 0)
		return (0);
	return (-1);
}

/*
**	Assumes we are at the beginning of a line, with a freshly initalized st_cmd.
**	Reads stdin, breaks when \n is entered, returning the filled st_cmd.
**	Returns 0 on quit, return -1 on ctrl + c
*/

int		input_loop(t_st_cmd *st_cmd, t_vars *vars, int mode)
{
	char	buf[BUF_SIZE + 1];
	char	c;
	int		ret;

	ft_bzero(buf, BUF_SIZE + 1);
	print_prompt(st_cmd);
	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		buf[ft_strlen(buf)] = c;
		//magic_print(buf);
		if (is_valid_escape(buf) == 0)
			continue ;
		ret = checkers(st_cmd, vars, buf, mode);
		if (ret == input_stop)
			return (-1);
		else if (ret == input_break)
			break;
		reposition_cursor(st_cmd);
		ft_bzero(buf, BUF_SIZE + 1);
	}
	if (st_cmd->st_txt->data_size > INT_MAX)
	{
		ft_dprintf(2, "error: maximum input size exceeded\n");
		return (-1); // print error ?  move inside loop ?
	}
	if (ret >= 0)
		return (1);
	return (0);
}
