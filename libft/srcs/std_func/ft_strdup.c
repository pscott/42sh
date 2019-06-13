#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char *res;

	if (!s1)
		return (NULL);
	if (!(res = ft_strnew(ft_strlen(s1))))
		return (NULL);
	return (ft_strcpy(res, s1));
}
