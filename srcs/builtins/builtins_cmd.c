#include "builtins.h"
#include "errors.h"

static int	job_control_id(t_cmd_id cmd_id)
{
	if (cmd_id == cmd_jobs)
		return (1);
	else if (cmd_id == cmd_fg)
		return (1);
	else if (cmd_id == cmd_bg)
		return (1);
	return (0);
}

static int	case_job_control(t_cmd_id cmd_id, char **argv)
{
	int	ret;

	ret = 0;
	if (cmd_id == cmd_jobs)
		ret = case_jobs(argv);
	else if (cmd_id == cmd_fg)
		ret = case_fg(argv);
	else if (cmd_id == cmd_bg)
		ret = case_bg(argv);
	return (ret);
}

/*
**	Executes the builtin corresponding to the cmd_id parameter (see cmd enums).
**	Use check_builtins before calling exec_builtins
*/

int			exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id)
{
	int				ret;

	ret = 0;
	if (!argv)
		ret = 1;
	else if (cmd_id == cmd_exit)
		ret = case_exit(argv, &vars->cmd_value);
	else if (cmd_id == cmd_env)
		ret = case_env(argv, &vars->env_vars);
	else if (cmd_id == cmd_cd)
		ret = case_cd(argv, &vars->env_vars);
	else if (cmd_id == cmd_type)
		ret = case_type(argv, vars);
	else if (cmd_id == cmd_hash)
		ret = case_hash(argv, vars);
	else if (cmd_id == cmd_echo)
		ret = case_echo(argv);
	else if (job_control_id(cmd_id))
		ret = case_job_control(cmd_id, argv);
	ft_free_ntab(argv);
	return (ret);
}

/*
**	Checks if argv[0] is a builtin or not. Returns the corresponding enum
**	command value in case of success ; returns 0 on failure.
*/

int			check_builtins(char **argv)
{
	if (ft_strequ(argv[0], "exit"))
		return (cmd_exit);
	else if (ft_strequ(argv[0], "env"))
		return (cmd_env);
	else if (ft_strequ(argv[0], "cd"))
		return (cmd_cd);
	else if (ft_strequ(argv[0], "hash"))
		return (cmd_hash);
	else if (ft_strequ(argv[0], "type"))
		return (cmd_type);
	else if (ft_strequ(argv[0], "echo"))
		return (cmd_echo);
	else if (ft_strequ(argv[0], "jobs"))
		return (cmd_jobs);
	else if (ft_strequ(argv[0], "fg"))
		return (cmd_fg);
	else if (ft_strequ(argv[0], "bg"))
		return (cmd_bg);
	return (0);
}
