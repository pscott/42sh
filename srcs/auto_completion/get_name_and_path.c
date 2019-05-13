#include "libft.h"
#include "line_editing.h"
/*
int		name_get(t_list *lst, char **name)
{
	char	*str;
	int		i;
	int		k;

	if (!(str = lst_to_string(lst)))// lst est bon mais pas str
		return (ERR_MALLOC);
//	ft_putstr("str : ");
//	ft_putendl(str);
//	ft_putchar('\n');
	i = ft_strlen(str) - 1;
	k = -1;
	if (ft_isspace(str[i]))
	{
		*name = NULL;
		return (free_ptr(str, 0));
	}
	while (i >= 0 && str[i] != '/' && !ft_isspace(str[i]))
		i--;
	i++;
	if (!(*name = ft_strdup(str + i)))
		return (free_ptr(str, ERR_MALLOC));
	return (free_ptr(str, 0));
}

int		path_get(t_list *lst, char **path)
{
	char	*str;
	int		i;
	int		k;
	int		l;

	if (!(str = lst_to_string(lst)))
		return (ERR_MALLOC);
	i = ft_strlen(str) - 1;
	l = 0;
	k = -1;
	while (i >= 0 && !ft_isspace(str[i]))
	{
		if (str[i] == '/' && k == -1)
			k = i;
		i--;
	}
	i++;
	if (!(*path = ft_memalloc(sizeof(char) * (k + i + 1))))
		return (free_ptr(str, ERR_MALLOC));
	while (i <= k)
		(*path)[l++] = str[i++];
	return (free_ptr(str, 0));
}*/
