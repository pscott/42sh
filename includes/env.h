#ifndef ENV_H
# define ENV_H

# include "ftsh.h"
# define PATH_DEFAULT_VALUE "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."
# define TERM_DEFAULT_VALUE "xterm-256color"
# define TERM_DEFAULT_LEN 15
# define FCEDIT_DEFAULT_VALUE "vim"

/*
** init_env.c
*/

char				**init_env(const char **env);

/*
** shlvl.c
*/

void				set_shlvl(char ***env);

/*
** environ_utils.c
*/

int					get_envline_index(char *search, char **env);
char				*get_envline_value(char *search, char **env);
char				*get_envline(char *search, char **env);

/*
** environ_set.c
*/

void				set_env_var(char *var_name, char *var_value, char ***env);

/*
** environ_unset.h
*/

void				unset_env_var(char *var_name, char ***env);
void				set_default_shell_vars(t_vars *vars);
void				add_variables(char *var_name, char *var_value,
	char ***ntab);
char				*get_varline_from_vartab(char *search, char **ntab);
char				*get_varline_value(char *search, char **ntab);
char				*concat_for_vartab(char *var_name, char *var_value);
char				**append_line_to_ntab(char *new_line, char **old_tab);
char				**delete_line_ntab(int index_to_del, const char **old_tab);
int					str_equ_varname(char *search, char *varline);
char				*get_varline_name(char *varline);
void				add_varline(char *varline, char ***ntab);
char				*get_name_from_varline(char *varline);
char				**get_ntab_cpy(char **src_tab);
void				cpy_ntab(char **new_tab, const char **old_tab);
void				ft_memdel_ntab(char ***ntab);
#endif
