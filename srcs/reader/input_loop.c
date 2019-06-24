#include "ftsh.h"
#include "input.h"
#include "libterm.h"
#include "line_editing.h"
#include <limits.h>
#include "errors.h"

static int	cmp_special_keys_versus_own_len(char *buf)
{
	if (ft_strncmp(buf, RIGHTARROW, ARROW_LEN + 1) == 0
			|| ft_strncmp(buf, LEFTARROW, ARROW_LEN + 1) == 0
			|| ft_strncmp(buf, UPARROW, ARROW_LEN + 1) == 0
			|| ft_strncmp(buf, DOWNARROW, ARROW_LEN + 1) == 0
			|| ft_strncmp(buf, HOME, HOME_LEN + 1) == 0
			|| ft_strncmp(buf, END, END_LEN + 1) == 0
			|| ft_strncmp(buf, DEL, DEL_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_UP, ALT_UP_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_DOWN, ALT_DOWN_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_RIGHT, ALT_RIGHT_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_LEFT, ALT_LEFT_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_X, ALT_X_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_C, ALT_C_LEN + 1) == 0
			|| ft_strncmp(buf, ALT_V, ALT_V_LEN + 1) == 0
			|| ft_strncmp(buf, F1_KEY, F1_KEY_LEN + 1) == 0)
		return (1);
	return (0);
}

static int	cmp_special_keys_versus_buf_len(char *buf, size_t len)
{
	if (ft_strncmp(buf, RIGHTARROW, len) == 0
			|| ft_strncmp(buf, LEFTARROW, len) == 0
			|| ft_strncmp(buf, UPARROW, len) == 0
			|| ft_strncmp(buf, DOWNARROW, len) == 0
			|| ft_strncmp(buf, DEL, len) == 0
			|| ft_strncmp(buf, ALT_UP, len) == 0
			|| ft_strncmp(buf, ALT_DOWN, len) == 0
			|| ft_strncmp(buf, ALT_RIGHT, len) == 0
			|| ft_strncmp(buf, ALT_LEFT, len) == 0
			|| ft_strncmp(buf, ALT_X, len) == 0
			|| ft_strncmp(buf, ALT_C, len) == 0
			|| ft_strncmp(buf, ALT_V, len) == 0
			|| ft_strncmp(buf, F1_KEY, len) == 0)
		return (1);
	return (0);
}

/*
**	Returns -1 if buffer is NOT an escape sequence.
**	Returns 0 if buffer might be an escape sequence.
**	Returns 1 if buffer IS an escape sequence.
*/

int			is_valid_escape(char *buf)
{
	size_t		len;
	size_t		last;

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
	if (cmp_special_keys_versus_own_len(buf))
		return (1);
	if (cmp_special_keys_versus_buf_len(buf, len))
		return (0);
	return (-1);
}

/*
**	Assumes we are at the beginning of a line, with a freshly initalized st_cmd.
**	Reads stdin, breaks when \n is entered, returning the filled st_cmd.
**	Returns 0 on quit, return -1 on ctrl + c
*/

int			input_loop(t_st_cmd *st_cmd, t_vars *vars, int mode)
{
	char				buf[BUF_SIZE + 1];
	char				c;
	ssize_t				ret;

	ft_bzero(buf, sizeof(buf));
	print_prompt(st_cmd);
	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		buf[ft_strlen(buf)] = c;
		if (is_valid_escape(buf) == 0)
			continue ;
		ret = checkers(st_cmd, vars, buf, mode);
		if (ret == input_stop)
			return (-1);
		else if (ret == input_break)
			break ;
		reposition_cursor(st_cmd, st_cmd->st_txt->tracker);
		ft_bzero(buf, sizeof(buf));
	}
	if (st_cmd->st_txt->data_size >= INT_MAX)
	{
		print_errors(-1, ERR_MAX_INPUT_STR, NULL);
		return (0);
	}
	if (ret >= 0)
		return (1);
	if (ret == -1)
		clean_exit(-1, READ_ERR);
	return (0);
}
