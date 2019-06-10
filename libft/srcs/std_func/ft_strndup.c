#include "libft.h"
#include <stdlib.h>

char		*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strnlen(s1, n) < n ? ft_strnlen(s1, n) : n;
	if (!(res = ft_strnew(len)))
		return (NULL);
	ft_strncpy(res, s1, len);
	res[len] = 0;
	return (res);
}
