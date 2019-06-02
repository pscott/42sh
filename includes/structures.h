#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef unsigned char	t_bool;
typedef struct			s_vars
{
	char				**env_vars;
	char				**shell_vars;
	struct s_hashmap	*hashmap;
	int					cmd_value;
	t_bool				verbose;
}						t_vars;

#endif
