#ifndef BUILTINS_H
# define BUILTINS_H

# include "42sh.h"

enum	{args_nb, arg_not_digit};
enum	{cmd_cd = 1, cmd_echo, cmd_env, cmd_exit, cmd_setenv, cmd_unsetenv
	, cmd_hash, cmd_type};
t_bool	check_builtins(char **argv);
t_bool	exec_builtins(char **argv, t_vars *vars, int cmd_id);

int		case_cd(char **argv, char ***env);
int		case_hash(char **argv, t_vars *vars);
int		get_exit_value(char **argv);
void	print_exit(void);
int		case_exit(char **argv, int *exitno);
int		case_type(char **argv, t_vars *vars);
int		case_setenv(char **argv, t_vars *vars);
int		case_unsetenv(char **argv, t_vars *vars);
int		case_echo(char **argv);

/*
**	Exit utils
*/

int		ft_atol(const char *str);
int		word_is_num(char *str);
int		is_zero(char *str);

/*
**	CD utils
*/

char	*get_directory(const char *env_key, const char **env);
char	*get_cwd_value(const char **env);
char	*relative_directory(const char *path, const char **env);

#endif
