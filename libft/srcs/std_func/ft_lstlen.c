#include "libft.h"

size_t	ft_lstlen(t_list **head)
{
	size_t len;

	len = 0;
	if (head == NULL)
		return (len);
	while (*head)
	{
		len++;
		*head = (*head)->next;
	}
	return (len);
}
