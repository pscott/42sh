#include "auto_completion.h"
#include "cmd_parsing.h"
#include "errors.h"

static t_st_glob	*create_glob_link(int match)
{
	t_st_glob		*link;

	if ((!(link = (t_st_glob*)malloc(sizeof(t_st_glob) + 1))))
		clean_exit(1, 1);
	link->prev = NULL;
	link->next = NULL;
	link->name = NULL;
	link->keep = 0;
	link->match = match;
	return (link);
}

int					create_match_link_glob(t_st_glob **match, char *str, int m)
{
	t_st_glob		*new;
	char			*str_protected;

	str_protected = protect_special_characters(str);
	if (!(*match))
	{
		if (!((*match) = create_glob_link(m)))
			clean_exit(1, 1);
		if (!((*match)->name = ft_strdup(str_protected)))
			clean_exit(1, 1);
	}
	else
	{
		new = create_glob_link(m);
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
