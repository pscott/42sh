#include "libft.h"

unsigned int		ft_strlen_chars(const char *line, char *s)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	nb_chars;

	nb_chars = ft_strlen(s);
	i = 0;
	while (line && line[i] && line[i] != '\0')
	{
		j = 0;
		while (j < nb_chars)
		{
			if (line[i] == s[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
