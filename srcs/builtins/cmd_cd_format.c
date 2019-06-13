#include "builtins.h"

/*
**	Remove the useless space in real time
*/

static char		*remove_n_char(char *str, size_t pos)
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

/*
**	Cut the wrong slashs in the string
*/

static void		remove_wrong_slashs(char **dest)
{
	size_t	i;
	int		prev;
	size_t	k;

	k = 0;
	i = 0;
	prev = 0;
	while ((*dest)[i])
	{
		if (prev == '/' && (*dest)[i] == '/')
		{
			prev = (*dest)[i];
			(*dest) = remove_n_char(*dest, i);
			i = 0;
			prev = 0;
		}
		else
			prev = (*dest)[i];
		i++;
	}
	if (i > 0)
		i--;
	while (i > 0 && (*dest)[i] == ' ')
		i--;
	while ((*dest)[k] && ft_is_white_space((*dest)[k]))
		k++;
	if (k != i && (*dest)[i] == '/')
		(*dest) = remove_n_char(*dest, i);
}

/*
**	Remove the useless ./ in the string
*/

static char		*remove_useless_dots(char *dest)
{
	char	*new;
	int		i;

	i = 0;
	new = dest;
	while (new[i])
	{
		printf("%s\n", new);
		if (i != 0 && new[i] && new[i + 1] && new[i] == '/'
				&& new[i + 1] == '.')
		{
			new = remove_n_char(new, i);
			new = remove_n_char(new, i);
			i = 0;
		}
		i++;
	}
	return (new);
}

char			*format_path_string(char *dest)
{
	char	*new;

	printf("----------------------\n");
	new = ft_strdup(dest);
	remove_wrong_slashs(&new);
	new = remove_useless_dots(new);
	ft_printf("IN FORMAT PATH STRING : %s\n", new);
	printf("----------------------\n");
	ft_strdel(&dest);
	return (new);
}
