#include "libft.h"
#include "line_editing.h"

int			del_match(t_auto_comp *match)
{
	t_auto_comp		*tmp;

	(match) = (match)->prev;
/*	while (match && (match)->rank != 1)
	{
		tmp = (match);
		(match)->len = 0;
		(match)->type = 0;
		(match)->rank = 0;
		(match)->next = NULL;
		match = match->prev;
		ft_strdel(&(match->name));
		free(tmp);
	}
	if (!match)
		return (1);
	match->len = 0;
	match->type = 0;
	match->rank = 0;
	match->next = NULL;
	match->prev = NULL;
	ft_strdel(&(match->name));
	free(match);
*/	return (0);
}
