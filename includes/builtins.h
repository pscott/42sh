#ifndef BUILTINS_H
# define BUILTINS_H

# include "42sh.h"

enum	{CMD_CD = 1, CMD_ECHO, CMD_ENV, CMD_EXIT, CMD_SETENV, CMD_UNSETENV};
t_bool	check_builtins(char **argv);
t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id);

int		case_cd(char **argv, char ***env);

#endif
