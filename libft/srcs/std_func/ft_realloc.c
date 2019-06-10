#include "libft.h"

/*
**	Be careful, only works with char* !
**	Returns a newly allocated string if current_data_size + append_size is
**	bigger than curent_malloc_size, and copies the data string into it.
**	Updates current_malloc_size.
*/

char	*ft_realloc(char *data, size_t current_data_size,
		size_t *current_malloc_size, size_t append_size)
{
	char	*res;

	if (current_data_size + append_size < *current_malloc_size)
		return (data);
	while (*current_malloc_size < current_data_size + append_size)
		*current_malloc_size *= REALLOC_FACTOR;
	if (!(res = ft_strnew(*current_malloc_size * REALLOC_FACTOR)))
		return (NULL);
	res = (char*)ft_memcpy((void*)res, (void*)data,
		(sizeof(*data) * current_data_size));
	ft_memdel((void*)&data);
	return (res);
}
