#include "42sh.h"
#include "input.h"
#include "libterm.h"
#include "line_editing.h"

void	magic_print(char *buf) // debug
{
	int	i;

	i = 0;
	execute_str(SAVE_CURSOR);
	move_cursor(0, 0);
	while (i < BUF_SIZE + 1)
	{
		ft_dprintf(2, "%-3d", buf[i]);
		i++;
	}
	execute_str(RESTORE_CURSOR);
}

/*
**	Inserts some text in the current st_cmd
*/

void	insert_txt(t_st_cmd *st_cmd, const char *buf)
{
	t_st_txt	*st_txt;
	size_t		print_len;
	size_t		tmp;


	st_txt = st_cmd->st_txt;
	print_len = ft_printable_len(buf);
	st_txt->txt = ft_realloc(st_txt->txt, st_txt->data_size,
			&st_txt->malloc_size, print_len);
	insert_str(st_cmd, buf, print_len);
	st_txt->data_size += print_len;
	tmp = st_txt->tracker + print_len;
	write_st_cmd(st_cmd);
	st_txt->tracker = tmp;
	get_pos(st_cmd, st_cmd->st_txt->tracker);
}

/*
**	Returns -1 if buffer is NOT an escape sequence.
**	Returns 0 if buffer might be an escape sequence.
**	Returns 1 if buffer IS an escape sequence.
*/

static int is_valid_escape(char *buf)
{
	int		len;
	int		last;

	len = ft_strlen(buf);
	if (len >= BUF_SIZE)
		return (-1);
	last = len > 0 ? len - 1 : 0;
	if (buf[last] == '\x03' || buf[last] == '\x04')
	{
		*buf = buf[last];
		ft_bzero(&buf[1], BUF_SIZE);
		return (-1);
	}
	last = len > 0 ? len - 1 : 0;
	if (ft_strncmp(buf, RIGHTARROW, ARROW_LEN + 1) == 0 || ft_strncmp(buf, LEFTARROW, ARROW_LEN + 1) == 0
		|| ft_strncmp(buf, UPARROW, ARROW_LEN + 1) == 0 || ft_strncmp(buf, DOWNARROW, ARROW_LEN + 1) == 0
		|| ft_strncmp(buf, HOME, HOME_LEN + 1) == 0 || ft_strncmp(buf, END, END_LEN + 1) == 0)
		return (1);
	if (ft_strncmp(buf, RIGHTARROW, len) == 0 || ft_strncmp(buf, LEFTARROW, len) == 0
		|| ft_strncmp(buf, UPARROW, len) == 0 || ft_strncmp(buf, DOWNARROW, len) == 0)
		return (0);
	return (-1);
}

/*
**	Assumes we are at the beginning of a line, with a freshly initalized st_cmd.
**	Reads stdin, breaks when \n is entered, returning the filled st_cmd.
**	Returns 0 on quit, return -1 on ctrl + c
*/

int		input_loop(t_st_cmd *st_cmd, t_vars *vars)
{
	char	buf[BUF_SIZE + 1];
	char	c;
	int		ret;
	t_pos	tmp_pos;

	ft_bzero(buf, BUF_SIZE + 1);
	print_prompt(st_cmd);
	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		buf[ft_strlen(buf)] = c;
		if (is_valid_escape(buf) == 0)
			continue ;
		retrieve_pos(&tmp_pos);
		if (tmp_pos.row < st_cmd->start_pos.row)
		{
			execute_str(BEGIN_LINE);
			execute_str(CLEAR_BELOW);
			retrieve_pos(&st_cmd->start_pos);
			write_from_start(st_cmd);
		}
		if (check_for_signal(buf))
			return (-1);
		else if (check_for_arrows(st_cmd, buf) || check_for_delete(st_cmd, buf)
			|| check_for_tab(st_cmd, buf, vars) || check_for_quit(st_cmd, buf))
			;
		else if (check_for_enter(buf))
		{
			ft_strncpy(buf, "\n", 1);
			st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
			get_pos(st_cmd, st_cmd->st_txt->tracker);
			reposition_cursor(st_cmd);
			insert_txt(st_cmd, (const char*)buf);
			write(STDIN_FILENO, "\n", 1);
			break ;
		}
		else
			insert_txt(st_cmd, (const char*)buf);
		reposition_cursor(st_cmd);
		ft_bzero(buf, BUF_SIZE + 1);
	}
	if (ret >= 0)
		return (1);
	return (0);
}
