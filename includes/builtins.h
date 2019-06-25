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
	cmd_exit,
	cmd_hash,
	cmd_type,
	cmd_test,
	cmd_set,
	cmd_unset,
	cmd_export,
	cmd_history,
	cmd_fc
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
}					t_cmd_test;

int					check_builtins(char **argv);
int					exec_builtins(char **argv, t_vars *vars, t_cmd_id cmd_id);

int					case_cd(char **argv, t_vars *vars);
int					case_hash(char **argv, t_vars *vars);
int					get_exit_value(char **argv);
void				print_exit(void);
int					case_exit(char **argv, int *exitno);
int					case_type(char **argv, t_vars *vars);
int					case_echo(char **argv);
int					case_test(char **argv);
int					case_set(char **argv, t_vars *vars);
int					case_unset(char **argv, t_vars *vars);
int					case_export(char **argv, t_vars *vars);
int					case_fc(char **argv);
int					case_history(char **argv);

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
char				*relative_directory(const char *path, const char **env,
						int *cdpath);
int					get_cd_options(char **argv, int *pos);
char				*cut_path_string(char *str, int slash);
int					get_path(char ***path, t_vars *vars);
int					check_cdpath_var(const char *path, const char **env,
						char **tmp, int *cdpath);
void				format_path_string(char **dest);
char				*remove_n_char(char *str, size_t pos);
int					change_environ(char *new_wd, t_vars *vars,
		int opt, int display);
int					check_full_access(char **dest, char *msg);

/*
**	Env utils
*/

int					check_env_flags(char **argv, int *pos);

/*
**	Test utils
*/

char				**check_inv(char **argv, int *inv);

int					test_flag_b(char *path);
int					test_flag_c(char *path);
int					test_flag_d(char *path);
int					test_flag_e(char *path);
int					test_flag_f(char *path);
int					test_flag_g(char *path);
int					test_flag_cap_l(char *path);
int					test_flag_p(char *path);
int					test_flag_r(char *path);
int					test_flag_cap_s(char *path);
int					test_flag_s(char *path);
int					test_flag_u(char *path);
int					test_flag_w(char *path);
int					test_flag_x(char *path);
int					test_flag_z(char *path);

int					test_flag_sym_eq(char *left, char *right, int *result);
int					test_flag_sym_noteq(char *left, char *right, int *result);
int					test_flag_eq(char *left, char *right, int *result);
int					test_flag_ne(char *left, char *right, int *result);
int					test_flag_ge(char *left, char *right, int *result);
int					test_flag_lt(char *left, char *right, int *result);
int					test_flag_le(char *left, char *right, int *result);
int					check_longlong(char *str, long long *value);
int					get_unary_option(char *arg);
int					get_binary_option(char *arg);
int					check_test_errors(char **argv, int ac);
int					check_unary_values(char *path, int uflag);
int					check_binary_values(char *right, char *left, int biflag,
					int *result);

/*
**	Export utils
*/

int					export_usage(char c);
int					check_string_export(char *str);
int					parse_options_export(char **argv, int *i);

#endif
