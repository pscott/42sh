#include "libft.h"
#include "line_editing.h"

static	void	swap(t_auto_comp **l1, t_auto_comp **l2)
{
	t_auto_comp		*tmp;

	tmp = *l2;
	*l2 = *l1;
	*l1 = tmp;
}

static	int		lst_cmp(t_list *lst1, t_list *lst2)
{
	int				c1;
	int				c2;

	while (lst1->prev)
		lst1 = lst1->prev;
	while (lst2->prev)
		lst2 = lst2->prev;
	while (lst1 && lst2 && lst1->c == lst2->c)
	{
		lst1 = lst1->next;
		lst2 = lst2->next;
	}
	if (lst1 == NULL)
		c1 = 0;
	else
		c1 = lst1->c;
	if (lst2 == NULL)
		c2 = 0;
	else
		c2 = lst2->c;
	return (c2 - c1);
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
