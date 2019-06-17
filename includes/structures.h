#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct			s_vars
{
	char				**env_vars;
	char				**shell_vars;
	struct s_hashmap	*hashmap;
	char				*copy;
	int					cmd_value;
	int					verbose;
	char				**assign_tab;
}						t_vars;

#endif
