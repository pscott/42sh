#include "builtins.h"

static int	exec_remaining_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id)
{
	if (cmd_id == cmd_jobs)
		return (case_jobs(argv));
	else if (cmd_id == cmd_fg)
		return (case_fg(argv));
	else if (cmd_id == cmd_bg)
		return (case_bg(argv));
	else if (cmd_id == cmd_fc)
		return (case_fc(argv));
	else if (cmd_id == cmd_history)
		return (case_history(argv));
	else if (cmd_id == cmd_test)
		return (case_test(argv));
	else if (cmd_id == cmd_set)
		return (case_set(argv, vars));
	else if (cmd_id == cmd_unset)
		return (case_unset(argv, vars));
	else if (cmd_id == cmd_export)
		return (case_export(argv, vars));
	ft_free_ntab(argv);
	return (0);
}

/*
**	Executes the builtin corresponding to the cmd_id parameter (see cmd enums).
**	Use check_builtins before calling exec_builtins
*/

int			exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id)
{
	int				ret;

	ret = 0;
	if (cmd_id == cmd_exit)
		ret = case_exit(argv, &vars->cmd_value);
	else if (cmd_id == cmd_cd)
		ret = case_cd(argv, &vars->env_vars);
	else if (cmd_id == cmd_type)
		ret = case_type(argv, vars);
	else if (cmd_id == cmd_hash)
		ret = case_hash(argv, vars);
	else if (cmd_id == cmd_echo)
		ret = case_echo(argv);
	return (exec_remaining_builtins(argv, vars, cmd_id));
}
