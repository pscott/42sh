#include "ftsh.h"
#include "input.h"
#include "line_editing.h"


/*
**	Inserts some text in the current st_cmd
*/

static void	insert_txt(t_st_cmd *st_cmd, const char *buf)
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
**	Utility function that gets called when enter key is pressed
*/

static void pressed_enter(t_st_cmd *st_cmd, char *buf)
{
	ft_strncpy(buf, "\n", 1);
	st_cmd->st_txt->tracker = st_cmd->st_txt->data_size;
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	reposition_cursor(st_cmd);
	insert_txt(st_cmd, (const char*)buf);
	execute_str(PRINT_LINE);
}

int			checkers(t_st_cmd *st_cmd, t_vars *vars, char *buf)
{
	int	ret;

	if ((ret = check_for_signal(buf)) > 0)
		return (ret);
	else if (check_for_arrows(st_cmd, buf) || check_for_delete(st_cmd, buf)
			|| check_for_tab(st_cmd, buf, vars))
		;
	else if ((ret = check_for_search_histo(st_cmd, buf)))
	{
		if (ret == ctrl_c_case)
			return (input_stop);
		if (ret == enter_case || ret == ctrl_c_case)
			return (input_break);
	}
	else if ((ret = check_for_quit(st_cmd, buf)) == 1)
		return (input_break);
	else if (ret == -1)
		;
	else if (check_for_enter(buf))
	{
		pressed_enter(st_cmd, buf);
		return (input_break);
	}
	else
		insert_txt(st_cmd, (const char*)buf);
	return (input_continue);
}
