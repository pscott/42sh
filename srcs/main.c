#include "builtins.h"
#include "line_editing.h"
#include "hashmap.h"
#include "history.h"
#include "signals.h"

int			is_full_of_whitespaces(const char *input)
{
	int		i;

	if (!input)
		return (1);
	i = -1;
	while (input[++i])
	{
		if (!ft_is_white_space(input[i]))
			return (0);
	}
	return (1);
}

/*
**	Utility function to free all alloacted variables and reset the old
**	terminal attributes.
**	Returns the last cmd value.
*/

static int	free_variables(t_vars *vars, t_st_cmd *st_cmd)
{
	int	ret;

	print_exit();
	write_to_history(st_cmd, (const char **)vars->env_vars);
	free_all_st_cmds(&st_cmd);
	ret = vars->cmd_value;
	free_vars(vars);
	reset_terminal_settings();
	return (ret);
}

/*
**	Initialize variables, read input with input_loop.
**	If reading input fails or first byte of input is 0, exits.
**	Else, calls handle_input for lexing, creating and executing the AST.
**	On exit, writes history and frees everything that was previously allocated.
*/

int			main(int argc, char **argv, char **env)
{
	t_st_cmd		*st_cmd;
	t_vars			vars;
	int				ret;

	if (setup_terminal_settings() > 0)
		return (EXIT_FAILURE);
	if (init_vars(&vars, argc, argv, env) == 1)
		return (EXIT_FAILURE);
	signals_setup();
	st_cmd = init_st_cmd((const char **)vars.shell_vars);
	get_st_cmd(&st_cmd);
	while (42)
	{
		if ((ret = input_loop(st_cmd, &vars, regular)) == 0
				|| !*st_cmd->st_txt->txt)
			break ;
		else if (ret > 0 && !is_full_of_whitespaces(st_cmd->st_txt->txt))
			vars.cmd_value = handle_input(st_cmd, &vars);
		st_cmd = reset_st_cmd(st_cmd);
	}
	ret = free_variables(&vars, st_cmd);
	return (ret);
}
