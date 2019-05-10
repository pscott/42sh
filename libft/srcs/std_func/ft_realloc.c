/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:53:22 by pscott            #+#    #+#             */
/*   Updated: 2019/04/18 16:26:33 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Be careful, only works with char* !
*/

char	*ft_realloc(char *data, size_t current_data_size,
		size_t *current_malloc_size, size_t append_size)
{
	char	*res;

	if (current_data_size + append_size < *current_malloc_size)
		return (data);
	if (!(res = ft_strnew(*current_malloc_size * REALLOC_FACTOR)))
		return (NULL);
	*current_malloc_size *= REALLOC_FACTOR;
	res = (char*)ft_memcpy((void*)res, (void*)data, (sizeof(*data) * current_data_size));
	ft_memdel((void*)&data);
	return (res);
}
