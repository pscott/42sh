/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:19 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		front_back_split(t_list *src, t_list **fref, t_list **bref)
{
	t_list *fast;
	t_list *slow;

	slow = src;
	fast = src->next;
	while (fast)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*fref = src;
	*bref = slow->next;
	slow->next = NULL;
}

static	size_t	max_list(t_list *a, t_list *b)
{
	if (a->content_size > b->content_size)
		return (a->content_size);
	else
		return (b->content_size);
}

static	t_list	*sorted_merge(t_list *a, t_list *b)
{
	t_list *res;

	res = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_memcmp(a->content, b->content, max_list(a, b)) <= 0)
	{
		res = a;
		res->next = sorted_merge(a->next, b);
	}
	else
	{
		res = b;
		res->next = sorted_merge(a, b->next);
	}
	return (res);
}

void			ft_lstsort(t_list **head)
{
	t_list	*tmp;
	t_list	*a;
	t_list	*b;

	tmp = *head;
	if ((tmp == NULL) || (tmp->next == NULL))
		return ;
	front_back_split(tmp, &a, &b);
	ft_lstsort(&a);
	ft_lstsort(&b);
	*head = sorted_merge(a, b);
}
