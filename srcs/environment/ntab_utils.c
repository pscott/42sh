#include "ftsh.h"

char	**ft_ntab_new(int size)
{
	char	**new_tab;
	int		i;

	if (!(new_tab = (char **)malloc(sizeof(char **)
				* (size + 1))))
		clean_exit(1, MALLOC_ERR);
	i = 0;
	while (i <= size)
	{
		new_tab[i] = NULL;
		i++;
	}
	return (new_tab);
}

/*
** cpy_ntab
** copy a ntab to another already allocated ntab
*/

void	cpy_ntab(char **new_tab, const char **old_tab)
{
	int		i;
	int		old_tab_len;

	old_tab_len = ft_ntab_len(old_tab);
	i = 0;
	while (i < old_tab_len)
	{
		if (!(new_tab[i] = ft_strdup(old_tab[i])))
			clean_exit(1, MALLOC_ERR);
		i++;
	}
}

/*
** get_ntab_cpy
** copy and return a freshly allocatd ntab
*/

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
		clean_exit(1, MALLOC_ERR);
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

	new_tab_len = ft_ntab_len(old_tab);
	if (!(new_tab = ft_ntab_new(new_tab_len)))
		clean_exit(1, MALLOC_ERR);
	i = 0;
	while (old_tab[i])
	{
		if (i < index_to_del)
		{
			if (!(new_tab[i] = ft_strdup(old_tab[i])))
				clean_exit(1, MALLOC_ERR);
		}
		if (i > index_to_del)
		{
			if (!(new_tab[i - 1] = ft_strdup(old_tab[i])))
				clean_exit(1, MALLOC_ERR);
		}
		i++;
	}
	new_tab[new_tab_len] = NULL;
	ft_memdel_ntab((char***)&old_tab);
	return (new_tab);
}
