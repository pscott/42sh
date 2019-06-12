/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:15 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:17 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
