#include "42sh.h"
#include "lexer.h"
#include "input.h"
#include "history.h"
#include "signals.h"
#include "line_editing.h"

t_bool	is_full_of_whitespaces(char *input)
{
	int		i;//TODO protect

	i = -1;
	while (input[++i])
	{
		if (!ft_is_white_space(input[i]))
			return (0);
	}
	return (1);
}

static void	free_vars(t_vars *vars)
{
	if (!vars)
		return ;
	ft_free_ntab(vars->env_vars);
	ft_free_ntab(vars->shell_vars);
}

int		main(int argc, char **argv, char **env)
{
	t_st_cmd		*st_cmd;
	t_vars			vars;
	int				ret;
	int				interactive;

	(void)argc;
	(void)argv;
	vars.env_vars = 0;
	vars.shell_vars = 0;
	vars.hashmap = init_hashmap(INIT_HASH_SIZE);
	if ((interactive = setup_terminal_settings()) == -1)
		return (EXIT_FAILURE);
	if (!(vars.env_vars = init_env((const char **)env)))
		return (EXIT_FAILURE);
	//vars->interactive = interactive;
	signal_setup();
	st_cmd = NULL;
	st_cmd = init_st_cmd((const char **)vars.env_vars);
	while (42)
	{
		if ((ret = input_loop(st_cmd, &vars)) == 0)
			break ; // free env, free st_cmd
		else if (ret > 0 && !is_full_of_whitespaces(st_cmd->st_txt->txt))
			handle_input(st_cmd, &vars);
		st_cmd = reset_st_cmd(st_cmd);
	}
	ft_printf("exit");
	print_line();
	write_to_history(st_cmd, (const char **)vars.env_vars);
	free_all_st_cmds(&st_cmd);
	free_vars(&vars);
	delete_hashmap(vars.hashmap);
	if (reset_terminal_settings() == 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
