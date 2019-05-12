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
		if (!is_white_spaces(input[i]))
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
	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	signal_setup();
	if (!(vars.env_vars = init_env((const char **)env)))
		return (EXIT_FAILURE);
	st_cmd = NULL;
	st_cmd = init_st_cmd((const char **)vars.env_vars);
	while (42)
	{
		if ((ret = input_loop(st_cmd)) == 0)
			break ; // free env, free st_cmd
		else if (ret > 0 && !is_full_of_whitespaces(st_cmd->st_txt->txt))
			handle_input(st_cmd, &vars);
		st_cmd = reset_st_cmd(st_cmd);
		//free st_cmd
	}
	write_to_history(st_cmd, (const char **)vars.env_vars);
	//free st_cmd
	//free_vars(vars);
	print_line();
	if (reset_terminal_settings() == 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
