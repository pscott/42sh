#include "ftsh.h"

char	**ft_ntab_new(int size)
{
	char	**new_tab;
	int		i;

	if (!(new_tab = (char **)malloc(sizeof(char **)
				* (size + 1))))
		clean_exit(1, 1);
	i = 0;
	while (i <= size)
	{
		new_tab[i] = NULL;
		i++;
	}
	return (new_tab);
}

void	cpy_ntab(char **new_tab, const char **old_tab)
{
	int		i;
	int		old_tab_len;

	old_tab_len = ft_ntab_len(old_tab);
	i = 0;
	while (i < old_tab_len)
	{
		if (!(new_tab[i] = ft_strdup(old_tab[i])))
			clean_exit(1, 1);
		i++;
	}
}

/*
** append_line_to_ntab
** return a new ntab with newline append to it
*/

char	**append_line_to_ntab(char *new_line, const char **old_tab)
{
	char	**new_tab;
	int		old_tab_len;

	old_tab_len = ft_ntab_len(old_tab);
	new_tab = ft_ntab_new(old_tab_len + 1);
	cpy_ntab(new_tab, old_tab);
	if (!(new_tab[old_tab_len] = ft_strdup(new_line)))
		clean_exit(1, 1);
	new_tab[old_tab_len + 1] = NULL;
	ft_free_ntab((char**)old_tab);
	return (new_tab);
}
