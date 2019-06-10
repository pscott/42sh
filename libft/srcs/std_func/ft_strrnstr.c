#include "libft.h"

char	*ft_strrnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == 0)
		return (NULL);
	i = len > ft_strlen(haystack) - 1 ? ft_strlen(haystack) - 1 : len;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i] == needle[j] && needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == 0)
		{
			return ((char *)&haystack[i - j]);
		}
		if (i - j > 0)
			i = i - j - 1;
		else
			return (NULL);
	}
	return (NULL);
}
