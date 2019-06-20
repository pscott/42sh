#ifndef BUILTINS_H
# define BUILTINS_H

# include "ftsh.h"
# include "history.h"

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
	cmd_type,
	cmd_set,
	cmd_unset,
	cmd_export,
}				t_cmd_id;

enum	{invalid_option};

int		check_builtins(char **argv);
int		exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id);

int		case_cd(char **argv, char ***env);
int		case_hash(char **argv, t_vars *vars);
int		get_exit_value(char **argv);
void	print_exit(void);
int		case_exit(char **argv, int *exitno);
int		case_env(char **argv, char ***env);
int		case_type(char **argv, t_vars *vars);
int		case_setenv(char **argv, t_vars *vars);
int		case_unsetenv(char **argv, t_vars *vars);
int		case_echo(char **argv);
int		case_set(char **argv, t_vars *vars);
int		case_unset(char **argv, t_vars *vars);
int		case_export(char **argv, t_vars *vars);

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
char	*relative_directory(const char *path, const char **env, int *cdpath);
int		get_cd_options(char **argv, int *pos);
char	*cut_path_string(char *str, int slash);
int		get_path(char ***path, t_vars *vars);
int		check_cdpath_var(const char *path, const char **env, char **tmp,
		int *cdpath);
void	format_path_string(char **dest);
char	*remove_n_char(char *str, size_t pos);
int		change_environ(char *new_wd, char ***env, int opt, int display);
int		check_full_access(char **dest, char *msg);

/*
**	Env utils
*/

int		check_env_flags(char **argv, int *pos);

#endif
