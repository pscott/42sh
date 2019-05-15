#ifndef BUILTINS_H
# define BUILTINS_H

# include "42sh.h"

enum {args_nb, arg_not_digit};
enum	{cmd_cd = 1, cmd_echo, cmd_env, cmd_exit, cmd_setenv, cmd_unsetenv, cmd_hash};
t_bool	check_builtins(char **argv);
t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id);

int		case_cd(char **argv, char ***env);
int		case_hash(char **argv, t_vars *vars);
int		get_exit_value(char **argv);
int		case_exit(char **argv);

#endif
