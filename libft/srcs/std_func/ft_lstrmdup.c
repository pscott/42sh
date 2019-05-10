/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:19 by pscott            #+#    #+#             */
/*   Updated: 2019/04/04 14:53:24 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	max_list(t_list *a, t_list *b)
{
	if (a->content_size > b->content_size)
		return (a->content_size);
	else
		return (b->content_size);
}

void			ft_lstrmdup(t_list *lst)
{
	t_list *l1;
	t_list *l2;
	t_list *dup;

	l1 = lst;
	while (l1 != NULL && l1->next != NULL)
	{
		l2 = l1;
		while (l2->next != NULL)
		{
			if (ft_memcmp(l1->content, l2->next->content,
						max_list(l1, l2->next)) == 0)
			{
				dup = l2->next;
				free(dup);
				l2->next = l2->next->next;
			}
			else
				l2 = l2->next;
		}
		l1 = l1->next;
	}
}
