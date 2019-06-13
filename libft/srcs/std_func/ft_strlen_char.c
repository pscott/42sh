#include "libft.h"

unsigned int		ft_strlen_char(const char *line, char c)
{
	unsigned int	i;

	i = 0;
	while (line && line[i] && line[i] != c && line[i] != '\0')
		i++;
	return (i);
}
