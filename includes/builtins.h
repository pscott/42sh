#ifndef BUILTINS_H
# define BUILTINS_H

# include "ftsh.h"
# include "history.h"

typedef enum		e_cd_error {
	args_nb = 1,
	arg_not_digit = 2
}					t_cd_error;

typedef enum		e_cmd_id {
	cmd_cd = 1,
	cmd_echo,
	cmd_env,
	cmd_exit,
	cmd_setenv,
	cmd_unsetenv,
	cmd_hash,
	cmd_type,
	cmd_test,
}					t_cmd_id;

typedef enum		e_cmd_test {
	op_b = 1,
	op_c,
	op_d,
	op_e,
	op_f,
	op_g,
	op_cap_l,
	op_p,
	op_r,
	op_cap_s,
	op_s,
	op_u,
	op_w,
	op_x,
	op_z,
	op_eq,
	op_ne,
	op_ge,
	op_lt,
	op_le,
	op_sym_eq,
	op_sym_noteq,
//	op_mark,
}					t_cmd_test;

enum				{invalid_option};

int					check_builtins(char **argv);
int					exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id);

int					case_cd(char **argv, char ***env);
int					case_hash(char **argv, t_vars *vars);
int					get_exit_value(char **argv);
void				print_exit(void);
int					case_exit(char **argv, int *exitno);
int					case_env(char **argv, char ***env);
int					case_type(char **argv, t_vars *vars);
int					case_setenv(char **argv, t_vars *vars);
int					case_unsetenv(char **argv, t_vars *vars);
int					case_echo(char **argv);
int					case_test(char **argv);

/*
**	Exit utils
*/

int					ft_atol(const char *str);
int					word_is_num(char *str);
int					is_zero(char *str);

/*
**	CD utils
*/

char				*get_directory(const char *env_key, const char **env);
char				*get_cwd_value(const char **env);
char				*relative_directory(const char *path, const char **env);

/*
**	Env utils
*/

int					check_env_flags(char **argv, int *pos);

/*
**	Test utils
*/

int					test_flag_b(char *path, int *result);
int					test_flag_c(char *path, int *result);
int					test_flag_d(char *path, int *result);
int					test_flag_e(char *path, int *result);
int					test_flag_f(char *path, int *result);
int					test_flag_g(char *path, int *result);
int					test_flag_cap_l(char *path, int *result);
int					test_flag_p(char *path, int *result);
int					test_flag_r(char *path, int *result);
int					test_flag_cap_s(char *path, int *result);
int					test_flag_s(char *path, int *result);
int					test_flag_u(char *path, int *result);
int					test_flag_w(char *path, int *result);
int					test_flag_x(char *path, int *result);
int					test_flag_z(char *path, int *result);

int					test_flag_sym_eq(char *left, char *right, int *result);
int					test_flag_sym_noteq(char *left, char *right, int *result);
int					test_flag_eq(char *left, char *right, int *result);
int					test_flag_ne(char *left, char *right, int *result);
int					test_flag_ge(char *left, char *right, int *result);
int					test_flag_lt(char *left, char *right, int *result);
int					test_flag_le(char *left, char *right, int *result);
int					check_longlong(char *str, long long *value);

#endif
