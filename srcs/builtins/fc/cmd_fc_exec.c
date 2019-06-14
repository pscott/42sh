#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

static int			print_exec_and_free(t_st_cmd *new_st_cmd, t_vars *new_vars)
{
	ft_dprintf(STDERR_FILENO, "%s\n", new_st_cmd->st_txt->txt);
	new_vars->cmd_value = handle_input(new_st_cmd, new_vars);
	free_st_txt(&(new_st_cmd->st_txt));
	return (0);
}

int					fc_execute_cmd(char *file, int type)
{
	t_st_cmd		*new_st_cmd;
	t_vars			*new_vars;
	int				fd;

	new_vars = get_vars(NULL);
	new_st_cmd = init_st_cmd((const char **)new_vars->env_vars);
	if (type == edit)
	{
		if ((fd = open(file, O_RDONLY)) == -1)
			return (1);
		while (get_next_line(fd, &(new_st_cmd->st_txt->txt)) > 0)
			print_exec_and_free(new_st_cmd, new_vars);
		if (close(fd) == -1)
			return (1);
	}
	else if (type == substitute)
	{
		if (!(new_st_cmd->st_txt->txt = ft_strdup(file)))
			clean_exit(1, 1);
		print_exec_and_free(new_st_cmd, new_vars);
	}
	free_st_cmd(new_st_cmd);
	get_vars(new_vars);
	return (0);
}
