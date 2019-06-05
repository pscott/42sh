#include "hashmap.h"

int	print_hash_invalid_option(char c)
{
	ft_dprintf(2, "-%c: invalid option\n", c);
	ft_dprintf(STDERR_FILENO,
						"hash usage [-lr] [-p pathname] [-d] [name ...]\n");
	return (0);
}
