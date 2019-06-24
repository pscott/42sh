#ifndef FTSH_H
# define FTSH_H

# include "structures.h"
# include "libft.h"
# include "libterm.h"
# include <sys/types.h>

# define SHELL_NAME "21sh"

typedef enum		e_exit
{
	EXIT,
	MALLOC_ERR,
	FORCE,
	READ_ERR
}					t_exit;

extern int				g_isatty;
extern struct termios	g_saved_attr;
extern int				g_can_exit;
/*
**	t_vars utility functions
*/

t_vars		*get_vars(t_vars *new_vars);
void		free_vars(t_vars *vars);
int			init_vars(t_vars *vars, int argc, char **argv, char **env);
void		reset_copy_vars(t_vars *vars);

/*
**	File descriptors funcs
*/

void		save_reset_stdfd(int mode);

/*
**	String tool
*/

void		print_introduction(void);
int			is_full_of_whitespaces(const char *input);
void		clean_exit(int exitno, t_exit reason);

char		*ft_strjoin_free_left(char *s1, const char *s2);
#endif
