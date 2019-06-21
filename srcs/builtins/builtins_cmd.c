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

	ret = 0;
	if (!argv)
		ret = 1;
	else if (cmd_id == cmd_exit)
		ret = case_exit(argv, &vars->cmd_value);
	else if (cmd_id == cmd_cd)
		ret = case_cd(argv, &vars->env_vars);
	else if (cmd_id == cmd_type)
		ret = case_type(argv, vars);
	else if (cmd_id == cmd_hash)
		ret = case_hash(argv, vars);
	else if (cmd_id == cmd_echo)
		ret = case_echo(argv);
	else if (cmd_id == cmd_test)
		ret = case_test(argv);
	else if (cmd_id == cmd_set)
		ret = case_set(argv, vars);
	else if (cmd_id == cmd_unset)
		ret = case_unset(argv, vars);
	else if (cmd_id == cmd_export)
		ret = case_export(argv, vars);
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
	if (ft_strcmp(argv[0], "exit") == 0)
		return (cmd_exit);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cmd_cd);
	if (ft_strcmp(argv[0], "hash") == 0)
		return (cmd_hash);
	if (ft_strcmp(argv[0], "type") == 0)
		return (cmd_type);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (cmd_echo);
	if (ft_strcmp(argv[0], "test") == 0)
		return (cmd_test);
	if (ft_strcmp(argv[0], "set") == 0)
		return (cmd_set);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (cmd_unset);
	if (ft_strcmp(argv[0], "export") == 0)
		return (cmd_export);
	return (0);
}
