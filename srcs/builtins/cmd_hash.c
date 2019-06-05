#include "ftsh.h"
#include "hashmap.h"

int		case_hash(char **argv, t_vars *vars)
{
	return (hash_builtin(vars, ft_ntab_len((const char**)argv), argv));
}
