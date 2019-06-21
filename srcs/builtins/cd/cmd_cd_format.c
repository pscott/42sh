#include "builtins.h"

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
			prev = (*dest)[i++];
	}
	if (i > 0)
		i -= 1;
	if (i > 0 && !ft_strncmp((*dest) + i, "/", 1))
		(*dest) = remove_n_char(*dest, i);
}

/*
**	Remove the useless /./ in the string
*/

static void		remove_useless_dots(char **dest)
{
	int		i;

	i = 0;
	while ((*dest)[i])
	{
		if (!ft_strncmp((*dest) + i, "/./", 3))
		{
			(*dest) = remove_n_char((*dest), i);
			(*dest) = remove_n_char((*dest), i);
			i = 0;
		}
		else
			i++;
	}
	if (i > 1)
		i -= 2;
	if (i > 0 && !ft_strncmp((*dest) + i, "/.", 2))
	{
		(*dest) = remove_n_char((*dest), i);
		(*dest) = remove_n_char((*dest), i);
	}
	else if (i == 0 && (*dest)[i] && (*dest)[i + 1] == '.')
		(*dest) = remove_n_char((*dest), i + 1);
}

void			format_path_string(char **dest)
{
	remove_wrong_slashs(dest);
	remove_useless_dots(dest);
}
