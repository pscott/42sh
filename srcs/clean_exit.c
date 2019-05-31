#include "42sh.h"
#include "history.h"
#include "input.h"

/*
** Utility function to reset the terminal settings and exit
*/

void	clean_exit(int exitno)
{
	t_st_cmd	*st_cmd;
	t_vars		*vars;

	st_cmd = get_st_cmd(NULL);
	vars = get_vars(NULL);
	if (isatty(STDIN_FILENO))
		write_to_history(st_cmd, (const char **)vars->env_vars);
	free_all_st_cmds(&st_cmd);
	free_vars(vars);
	delete_hashmap(vars->hashmap);
	save_reset_stdfd(0);
	reset_terminal_settings();
	exit(exitno);
}
