#include "hashmap.h"

t_bool	print_hash_invalid_option(char c)
{
	ft_dprintf(2, "-%c: invalid option\n", c);
	print_hash_usage();
	return (0);
}
