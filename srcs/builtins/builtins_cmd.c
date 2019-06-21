#include "builtins.h"
#include "errors.h"

/*
**	Executes the builtin corresponding to the cmd_id parameter (see cmd enums).
**	Returns 1 if it executed something.
**	Returns 0 if there was an error.
**	Updates vars->cmd_value with the corresponding builtin execution value.
**	Use check_builtins before calling exec_builtins
*/

int			exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id)
{
	int				ret;

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
	else if (cmd_id == cmd_setenv)
		ret = case_setenv(argv, vars);
	else if (cmd_id == cmd_unsetenv)
		ret = case_unsetenv(argv, vars);
	else if (cmd_id == cmd_echo)
		ret = case_echo(argv);
	else if (cmd_id == cmd_jobs)
		ret = case_jobs(argv);
	else if (cmd_id == cmd_fg)
		ret = case_fg(argv);
	else if (cmd_id == cmd_bg)
		ret = case_bg(argv);
	else
		ret = 0;
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
	if (ft_strequ(argv[0], "env"))
		return (cmd_env);
	if (ft_strequ(argv[0], "cd"))
		return (cmd_cd);
	if (ft_strequ(argv[0], "hash"))
		return (cmd_hash);
	if (ft_strequ(argv[0], "type"))
		return (cmd_type);
	if (ft_strequ(argv[0], "setenv"))
		return (cmd_setenv);
	if (ft_strequ(argv[0], "unsetenv"))
		return (cmd_unsetenv);
	if (ft_strequ(argv[0], "echo"))
		return (cmd_echo);
	if (ft_strequ(argv[0], "jobs"))
		return (cmd_jobs);
	if (ft_strequ(argv[0], "fg"))
		return (cmd_fg);
	if (ft_strequ(argv[0], "bg"))
		return (cmd_bg);
	return (0);
}
