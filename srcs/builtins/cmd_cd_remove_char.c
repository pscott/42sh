#include "builtins.h"

char		*remove_n_char(char *str, size_t pos)
{
	char	*new;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (pos > ft_strlen(str))
		return (str);
	if (!(new = (char*)malloc(sizeof(char) * ft_strlen(str))))
		clean_exit(1, 1);
	ft_bzero(new, ft_strlen(str));
	while (str[k])
	{
		if (k == pos)
			k++;
		if (!str[k])
			break ;
		new[i] = str[k];
		k++;
		i++;
	}
	ft_strdel(&str);
	return (new);
}
