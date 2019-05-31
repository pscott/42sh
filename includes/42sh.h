#ifndef TOSH_H
# define TOSH_H

# include "libft.h"
# include <stdlib.h>
# include "libterm.h"
# include <sys/types.h>
# include <pwd.h>
# include <unistd.h>
typedef unsigned char	t_bool;

# define ERROR_MEM clean_exit(1);
# define SHELL_NAME "42sh"//for error messages

typedef struct			s_vars
{
	char				**env_vars;
	char				**shell_vars;
	struct s_hashmap	*hashmap;
	int					cmd_value;
}						t_vars;

# include "hashmap.h"

/*
**	t_vars utility functions
*/

t_vars	*get_vars(t_vars *new_vars);
void	free_vars(t_vars *vars);

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

/*
**	File descriptors funcs
*/

void	save_reset_stdfd(int mode);

/*
** lexer_tools.c
*/

t_bool				is_delimiter(char c);

t_bool				is_full_of_whitespaces(char *input);

void			clean_exit(int exitno);
#endif
