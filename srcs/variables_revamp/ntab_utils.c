#include "ftsh.h"

void	ft_memdel_ntab(char ***ntab)
{
	ft_free_ntab(*ntab);
	*ntab = NULL;
}

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

char	**get_ntab_cpy(const char **src_tab)
{
	char	**new_tab;
	int		src_tab_len;

	src_tab_len = ft_ntab_len(src_tab);
	new_tab = ft_ntab_new(src_tab_len);
	cpy_ntab(new_tab, src_tab);
	return (new_tab);
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

/*
** delete_line_ntab
** realloc a new ntab without the line[index_to_del]
*/

char	**delete_line_ntab(int index_to_del, const char **old_tab)
{
	int		new_tab_len;
	char	**new_tab;
	int		i;

	new_tab_len = ft_ntab_len(old_tab) - 1;
	if (!(new_tab = ft_ntab_new(new_tab_len)))
		clean_exit(1, 1);
	i = 0;
	while (old_tab[i])
	{
		if (i < index_to_del)
		{
			if (!(new_tab[i] = ft_strdup(old_tab[i])))
				clean_exit(1, 1);
		}
		if (i > index_to_del)
		{
			if (!(new_tab[i - 1] = ft_strdup(old_tab[i])))
				clean_exit(1, 1);
		}
		i++;
	}
	new_tab[new_tab_len] = NULL;
	return (new_tab);
}
