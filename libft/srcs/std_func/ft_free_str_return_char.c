#include "libft.h"

char	ft_free_str_return_char(char **str, char c)
{
	ft_strdel(str);
	return (c);
}
