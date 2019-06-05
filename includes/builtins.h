#ifndef BUILTINS_H
# define BUILTINS_H

# include "ftsh.h"

typedef enum	e_cd_error {
	args_nb = 1,
	arg_not_digit = 2
}				t_cd_error;

typedef enum	e_cmd_id {
	cmd_cd = 1,
	cmd_echo,
	cmd_env,
	cmd_exit,
	cmd_setenv,
	cmd_unsetenv,
	cmd_hash,
	cmd_type
}				t_cmd_id;

int		check_builtins(char **argv);
int		exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id);

int		case_cd(char **argv, char ***env);
int		case_hash(char **argv, t_vars *vars);
int		get_exit_value(char **argv);
void	print_exit(void);
int		case_exit(char **argv, int *exitno);
int		case_env(char **argv, char ***env, t_vars *vars);
int		case_type(char **argv, t_vars *vars);
int		case_setenv(char **argv, char ***env);
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
