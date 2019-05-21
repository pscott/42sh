#include "libft.h"
#include "line_editing.h"
#include "errors.h"
#include <dirent.h>

static t_auto_comp	*create_auto_comp_link(void)
{
	t_auto_comp		*link;

	if ((!(link = (t_auto_comp*)malloc(sizeof(t_auto_comp) + 1))))
		return (NULL);
	link->prev = NULL;
	link->next = NULL;
	link->name = NULL;
	link->len = 0;
	return (link);
}

int					create_match_link(t_auto_comp **match, char *str, unsigned char type)
{
	t_auto_comp		*new;

	if (!(*match))
	{
		if (!((*match) = create_auto_comp_link()))
			return (ERR_MALLOC);
		if (!((*match)->name = ft_strdup(str)))
			return (1);
		//	return (free_ptr((*match), ERR_MALLOC));
		(*match)->len = ft_strlen(str);
	}
	else
	{
		if (!(new = create_auto_comp_link()))
			return (ERR_MALLOC);
		(*match)->next = new;
		new->prev = (*match);
		new->next = NULL;
		if (!(new->name = ft_strdup(str)))
			return (1);
		//	return (free_ptr(new, ERR_MALLOC));
		new->len = ft_strlen(str);
		(*match) = new;
	}
	return (0);
}
