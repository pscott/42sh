#ifndef FTSH_H
# define FTSH_H

# include "structures.h"
# include "libft.h"
# include <stdlib.h>
# include "libterm.h"
# include <sys/types.h>
# include <unistd.h>
# include "hashmap.h"

# define ERROR_MEM clean_exit(1)
# define SHELL_NAME "42sh"

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

void			magic_print(char *buf);//debug
#endif
