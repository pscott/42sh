#ifndef BUILTINS_H
# define BUILTINS_H

# include "42sh.h"

enum {ARGS_NB, ARG_NOT_DIGIT, ARG_TOO_LONG};
enum	{CMD_CD = 1, CMD_ECHO, CMD_ENV, CMD_EXIT, CMD_SETENV, CMD_UNSETENV, CMD_HASH};
t_bool	check_builtins(char **argv);
t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id);

int		case_cd(char **argv, char ***env);
int		case_hash(char **argv, t_vars *vars);
int		case_exit(char **argv);

#endif
