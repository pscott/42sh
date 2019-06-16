#include "ftsh.h"
#ifndef ENV_H
# define ENV_H

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

//
void				set_default_shell_vars(t_vars *vars);
void				add_variables(char *var_name, char *var_value, char ***ntab);
char				*get_varline_from_vartab(char *search, char **ntab);
char				*concat_for_vartab(char *var_name, char *var_value);
char				**append_line_to_ntab(char *new_line, char **old_tab);
#endif
