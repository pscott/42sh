#include "42sh.h"
#include "lexer.h"
#include "input.h"
#include "history.h"
#include "signals.h"
#include "builtins.h"
#include "line_editing.h"

t_bool	is_full_of_whitespaces(char *input)
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

int		main(int argc, char **argv, char **env)
{
	t_st_cmd		*st_cmd;
	t_vars			vars;
	int				ret;

	(void)argc;
	(void)argv;
	vars.hashmap = init_hashmap(INIT_HASH_SIZE);
	vars.cmd_value = 0;
	vars.shell_vars = NULL;
	get_vars(&vars);
	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	if (!(vars.env_vars = init_env((const char **)env)))
		return (EXIT_FAILURE);
	signal_setup();
	st_cmd = NULL; // useless ?
	st_cmd = init_st_cmd((const char **)vars.env_vars);
	while (42)
	{
		if ((ret = input_loop(st_cmd, &vars)) == 0 || !*st_cmd->st_txt->txt)
			break ; // free env, free st_cmd
		else if (ret > 0 && !is_full_of_whitespaces(st_cmd->st_txt->txt))
			handle_input(st_cmd, &vars);
//		if (isatty(STDIN_FILENO)) // debug
//			ft_printf("last_cmd value: %d\n", vars.cmd_value); // debug
		st_cmd = reset_st_cmd(st_cmd);
	}
	print_exit();
	if (isatty(STDIN_FILENO))
		write_to_history(st_cmd, (const char **)vars.env_vars);
	free_all_st_cmds(&st_cmd);
	free_vars(&vars);
	delete_hashmap(vars.hashmap);
	save_reset_stdfd(0);
	reset_terminal_settings();
	return (EXIT_SUCCESS);
}
