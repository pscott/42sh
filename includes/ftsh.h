#ifndef FTSH_H
# define FTSH_H

# include "libft.h"
# include <stdlib.h>
# include "libterm.h"
# include <sys/types.h>
# include <unistd.h>

# define ERROR_MEM clean_exit(1)
# define SHELL_NAME "42sh"

typedef struct			s_vars
{
	char				**env_vars;
	char				**shell_vars;
	struct s_hashmap	*hashmap;
	int					cmd_value;
}						t_vars;

typedef unsigned char	t_bool;
# include "hashmap.h"

/*
**	t_vars utility functions
*/

t_vars	*get_vars(t_vars *new_vars);
void	free_vars(t_vars *vars);

/*
**	File descriptors funcs
*/

void	save_reset_stdfd(int mode);

/*
**	String tool
*/

t_bool				is_full_of_whitespaces(const char *input);

void			clean_exit(int exitno);
#endif
