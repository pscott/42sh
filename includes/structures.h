#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>

typedef struct			s_vars
{
	char				**env_vars;
	char				**shell_vars;
	char				**env_save;
	char				**env_exported;
	struct s_hashmap	*hashmap;
	int					cmd_value;
	int					verbose;
	char				*copy;
	int					select_mode;
	size_t				select_start;
	size_t				select_end;
	char				**assign_tab;
	int					is_cr_sqt;
	int					interrupted;
}						t_vars;

#endif
