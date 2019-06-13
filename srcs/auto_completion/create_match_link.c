#include "auto_completion.h"
#include "errors.h"

char				*protect_special_characters(const char *str)
{
	char			*ret;
	int				count;
	int				i;
	unsigned int	k;

	i = -1;
	count = 0;
	while (str[++i])
		if (ft_is_metachar(str[i]))
			++count;
	if (!(ret = ft_strnew(i + count)))
		clean_exit(1, 1);
	i = 0;
	k = 0;
	while (str[i + 1])
	{
		if (ft_is_metachar(str[i]))
			ret[k++] = '\\';
		ret[k++] = str[i++];
	}
	ret[k] = str[i];
	return (ret);
}

static t_auto_comp	*create_auto_comp_link(void)
{
	t_auto_comp		*link;

	if ((!(link = (t_auto_comp*)malloc(sizeof(t_auto_comp) + 1))))
		clean_exit(1, 1);
	link->prev = NULL;
	link->next = NULL;
	link->name = NULL;
	return (link);
}

int					create_match_link(t_auto_comp **match, char *str)
{
	t_auto_comp		*new;
	char			*str_protected;

	str_protected = protect_special_characters(str);
	if (!(*match))
	{
		if (!((*match) = create_auto_comp_link()))
			clean_exit(1, 1);
		if (!((*match)->name = ft_strdup(str_protected)))
			clean_exit(1, 1);
	}
	else
	{
		new = create_auto_comp_link();
		(*match)->next = new;
		new->prev = (*match);
		new->next = NULL;
		if (!(new->name = ft_strdup(str_protected)))
			clean_exit(1, 1);
		(*match) = new;
	}
	ft_strdel(&str_protected);
	return (0);
}
