#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

static int			print_exec_and_free(t_st_cmd *st_cmd, t_vars *new_vars)
{
	char			*tmp;

	if (!(tmp = ft_strjoin(st_cmd->st_txt->txt, "\n")))
			clean_exit(1, 1);
	ft_dprintf(STDERR_FILENO, "%s\n", st_cmd->st_txt->txt);
	new_vars->cmd_value = handle_input(st_cmd, new_vars);
	st_cmd->hist_lst = insert_left(st_cmd->hist_lst, tmp, 1);
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	free_st_txt(&(st_cmd->st_txt));
	return (0);
}

int					fc_execute_cmd(t_st_cmd *st_cmd, char *file, int type)
{
	t_vars			*new_vars;
	int				fd;
	int				ret;

	new_vars = get_vars(NULL);
	free(st_cmd->st_txt->txt);
	if (type == edit)
	{
		if ((fd = open(file, O_RDONLY)) == -1)
			return (1);
		while (get_next_line(fd, &(st_cmd->st_txt->txt)) > 0)
			ret = print_exec_and_free(st_cmd, new_vars);
		if (close(fd) == -1)
			return (1);
	}
	else if (type == substitute)
	{
		if (!(st_cmd->st_txt->txt = ft_strdup(file)))
			clean_exit(1, 1);
		ret = print_exec_and_free(st_cmd, new_vars);
	}
	get_vars(new_vars);
	return (new_vars->cmd_value);
}
