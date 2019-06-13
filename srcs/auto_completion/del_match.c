#include "auto_completion.h"

int			del_match(t_auto_comp *match)
{
	t_auto_comp		*tmp;

	tmp = NULL;
	while (match && match->prev)
		(match) = (match)->prev;
	while (match && match->next)
	{
		tmp = (match);
		(match)->prev = NULL;
		ft_strdel(&(match->name));
		match = match->next;
		free(tmp);
	}
	if (!match)
		return (1);
	match->next = NULL;
	match->prev = NULL;
	ft_strdel(&(match->name));
	free(match);
	return (0);
}
