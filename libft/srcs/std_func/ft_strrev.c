#include "libft.h"

char	*ft_strrev(const char *s)
{
	size_t	len;
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	res = ft_strnew(len);
	while (len - i > 0)
	{
		res[i] = s[len - i - 1];
		i++;
	}
	return (res);
}
