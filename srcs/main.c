#include "ftsh.h"
#include "env.h"
#include "lexer.h"
#include "input.h"
#include "history.h"
#include "signals.h"
#include "builtins.h"
#include "line_editing.h"

t_bool		is_full_of_whitespaces(const char *input)
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
**	Utility function to initalize the shell variables, the environement, and
**	the last exit status.
*/

static int	init_vars(t_vars *vars, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	vars->hashmap = init_hashmap(INIT_HASH_SIZE);
	vars->cmd_value = 0;
	vars->shell_vars = NULL;
	vars->verbose = 1;//should be 0 ?
	get_vars(vars);
	if (!(vars->env_vars = init_env((const char **)env)))
		return (1);
	return (0);
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

	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	if (init_vars(&vars, argc, argv, env) == 1)
		return (EXIT_FAILURE);
	signals_setup();
	st_cmd = init_st_cmd((const char **)vars.env_vars);
	get_st_cmd(&st_cmd);
	while (42)
	{
		if ((ret = input_loop(st_cmd, &vars)) == 0 || !*st_cmd->st_txt->txt)
			break ;
		else if (ret > 0 && !is_full_of_whitespaces(st_cmd->st_txt->txt))
			handle_input(st_cmd, &vars);
		st_cmd = reset_st_cmd(st_cmd);
	}
	print_exit();
	write_to_history(st_cmd, (const char **)vars.env_vars);
	free_all_st_cmds(&st_cmd);
	free_vars(&vars);
	reset_terminal_settings();
	return (EXIT_SUCCESS);
}
