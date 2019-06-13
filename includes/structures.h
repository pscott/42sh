#ifndef STRUCTURES_H
# define STRUCTURES_H

#include <stdlib.h>

typedef struct			s_vars
{
	char				**env_vars;
	char				**shell_vars;
	struct s_hashmap	*hashmap;
	int					cmd_value;
	int					verbose;
	char				*copy;
	char				*select_start;
	int					select_mode;
	size_t				select_size;
}						t_vars;

#endif
