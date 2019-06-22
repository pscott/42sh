#include "errors.h"
#include "ftsh.h"
#include "builtins.h"
#include "execution.h"

static int			print_exec_and_free(t_st_cmd *st_cmd, t_vars *new_vars)
{
	char			*tmp;

	if (st_cmd && st_cmd->st_txt && st_cmd->st_txt->txt
		&& !st_cmd->st_txt->txt[0])
	{
		ft_strdel(&(st_cmd->st_txt->txt));
		new_vars->cmd_value = 1;
		return (0);
	}
	if (!(tmp = ft_strjoin(st_cmd->st_txt->txt, "\n")))
		clean_exit(1, 1);
	ft_dprintf(STDERR_FILENO, "%s\n", st_cmd->st_txt->txt);
	new_vars->cmd_value = handle_input(st_cmd, new_vars);
	st_cmd->hist_lst = insert_left(st_cmd->hist_lst, tmp, 1);
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	if (st_cmd && st_cmd->st_txt && st_cmd->st_txt->txt)
		ft_strdel(&(st_cmd->st_txt->txt));
	ft_strdel(&tmp);
	return (0);
}

static int			get_nbr_cr(int fd, int *i, int *r)
{
	char			*tmp;
	int				ret;

	ret = 0;
	tmp = NULL;
	while (get_next_line(fd, &tmp) > 0)
	{
		ret++;
		ft_strdel(&tmp);
	}
	lseek(fd, 0, SEEK_SET);
	*i = 0;
	*r = -1;
	return (ret);
}

static int			fc_execute_edit(t_st_cmd *st_cmd,
	t_vars *new_vars, char *file)
{
	int				fd;
	int				cr;
	char			**tmp;
	int				i;
	int				ret;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	cr = get_nbr_cr(fd, &i, &ret);
	if (!(tmp = (char**)malloc(sizeof(char*) * (cr + 1))))
		clean_exit(1, 1);
	tmp[cr] = NULL;
	while (get_next_line(fd, &(tmp[i])) > 0)
		i++;
	if (close(fd) == -1)
		return (1);
	i = 0;
	while (tmp[i])
	{
		if (!(st_cmd->st_txt->txt = ft_strdup(tmp[i++])))
			clean_exit(1, 1);
		ret = print_exec_and_free(st_cmd, new_vars);
	}
	ft_free_ntab(tmp);
	return (ret);
}

static int			reset_count(int *count)
{
	write(2, "Stop messing with the history file!\n", 36);
	*count = 0;
	return (1);
}

int					fc_execute_cmd(t_st_cmd *st_cmd, char *file, int type)
{
	t_vars			*new_vars;
	int				ret;
	static int		count = 0;

	new_vars = get_vars(NULL);
	ret = 0;
	if (st_cmd && st_cmd->st_txt && st_cmd->st_txt->txt)
		ft_strdel(&(st_cmd->st_txt->txt));
	count++;
	if (count > 50)
		return (reset_count(&count));
	if (type == edit)
		ret = fc_execute_edit(st_cmd, new_vars, file);
	else if (type == substitute)
	{
		if (!(st_cmd->st_txt->txt = ft_strdup(file)))
			clean_exit(1, 1);
		ret = print_exec_and_free(st_cmd, new_vars);
	}
	get_vars(new_vars);
	if (ret)
		new_vars->cmd_value = 1;
	return (new_vars->cmd_value);
}
