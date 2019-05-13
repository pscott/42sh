#include "hashmap.h"

unsigned int	hashfun(const char *input)
{
	unsigned int	hash_address;
	int				i;

	hash_address = 0;
	i = -1;
	while (input[++i])
	{
		hash_address = input[i] + (hash_address << 6) + (hash_address << 16)
			- hash_address;
	}
	//printf("hashfun: result of {%s} is %u\n", input, hash_address);
	return (hash_address);
}
