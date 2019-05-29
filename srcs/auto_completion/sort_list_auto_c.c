#include "libft.h"
#include "line_editing.h"

static	void	swap(t_auto_comp **l1, t_auto_comp **l2)
{
	t_auto_comp		*tmp;

	tmp = *l2;
	*l2 = *l1;
	*l1 = tmp;
}

void			new_sort_list(t_auto_comp **match)
{
	t_auto_comp		*ptr;
	t_auto_comp		*first;
	unsigned int	i;

	first = (*match);
	if (!first)
		return ;
	while (first->next)
	{
	//	ft_putendl(first->name);
		first = first->next;
	}
	first->next = NULL;
	while (first->prev)
	{
		first = first->prev;
	}
	ptr = first;
	while (first->next != NULL)
	{
		while (ptr)
		{
			if (ft_strcmp(ptr->name, first->name) > 0)
			{
				swap(&ptr, &first);
				ptr = first;
			}
			ptr = ptr->next;
		}
		first = first->next;
	}
}
