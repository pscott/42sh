#include "auto_completion.h"
#include "errors.h"

static t_auto_comp	*create_auto_comp_link(void)
{
	t_auto_comp		*link;

	if ((!(link = (t_auto_comp*)malloc(sizeof(t_auto_comp) + 1))))
		ERROR_MEM;
	link->prev = NULL;
	link->next = NULL;
	link->name = NULL;
	return (link);
}

int					create_match_link(t_auto_comp **match, char *str)
{
	t_auto_comp		*new;

	if (!(*match))
	{
		if (!((*match) = create_auto_comp_link()))
			ERROR_MEM;
		if (!((*match)->name = ft_strdup(str)))
			ERROR_MEM;
	}
	else
	{
		if (!(new = create_auto_comp_link()))
			return (ERR_MALLOC);
		(*match)->next = new;
		new->prev = (*match);
		new->next = NULL;
		if (!(new->name = ft_strdup(str)))
			ERROR_MEM;
		(*match) = new;
	}
	return (0);
}
