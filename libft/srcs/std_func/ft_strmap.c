#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	i;

	if (s && f)
	{
		if (!(res = ft_strnew(ft_strlen(s))))
			return (NULL);
		i = 0;
		while (s[i])
		{
			res[i] = (*f)(s[i]);
			i++;
		}
		return (res);
	}
	return (NULL);
}
