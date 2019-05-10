#include "lexer.h"
#include "libterm.h"
#include "reader.h"
#include "ast.h"
#include "history.h"

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
	int				ret;

	(void)argc;
	(void)argv;
	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	signal_setup();
	if (!(g_env = init_env((const char **)env)))
		return (EXIT_FAILURE);
	st_cmd = NULL;
	st_cmd = init_st_cmd((const char **)env);
	while (42)
	{
		if ((ret = input_loop(st_cmd)) == 0)
			break ; // free env, free st_cmd
		else if (ret > 0 && !is_full_of_whitespaces(st_cmd->st_txt->txt))
			handle_input(st_cmd, g_env);
		st_cmd = reset_st_cmd(st_cmd);
		//free st_cmd
	}
	write_to_history(st_cmd, (const char **)env);
	//free st_cmd
	ft_free_ntab(g_env);
	print_line();
	if (reset_terminal_settings() == 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
