#include "libft.h"

void	ft_lstappend(t_list **lst, t_list *new)
{
	if (lst == NULL || *lst == NULL)
		return ;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
}
