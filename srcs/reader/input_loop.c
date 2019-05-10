#include "reader.h"
#include "tosh.h"
#include "history.h"

void	magic_print(char *buf)
{
	int	i;

	i = 0;
	execute_str(SAVE_CURSOR);
	move_cursor(0, 0);
	while (i < BUF_SIZE + 1)
	{
		ft_dprintf(2, "%-3d ", buf[i]);
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
**	Assumes we are at the beginning of a line, with a freshly initalized st_cmd.
**	Reads stdin, breaks when \n is entered, returning the filled st_cmd.
**	Returns 0 on quit, return -1 on ctrl + c
*/

int		input_loop(t_st_cmd *st_cmd)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	ft_bzero(buf, BUF_SIZE + 1);
	retrieve_pos(&st_cmd->start_pos);
	print_prompt(st_cmd->st_prompt);
	while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
		magic_print(buf);
		buf[ret] = 0;
		if (check_for_signal(buf))
			return (-1);
		else if (check_for_arrows(st_cmd, buf) || check_for_delete(st_cmd, buf))
			;
		else if (check_for_enter(buf))
		{
			ft_strncpy(buf, "\n", 1);
			st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
			insert_txt(st_cmd, (const char*)buf);
			print_line();
			break ;
		}
		else if (check_for_quit(buf))
			return (0);
		else if (buf[0] < 0 || buf[0] == '\x1b') // checks for unicode and ANSI
			continue ;
		else
			insert_txt(st_cmd, (const char*)buf);
		reposition_cursor(st_cmd);
	}
	if (ret > 0)
		return (1);
	return (0);
}
