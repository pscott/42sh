#include "builtins.h"

int		case_hash(char **argv, t_vars *vars)
{
	return (hash_builtin(&vars->hashmap, ft_ntab_len((const char**)argv), argv));
}
