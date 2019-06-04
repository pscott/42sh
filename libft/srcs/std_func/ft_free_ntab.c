/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ntab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:27:55 by pscott            #+#    #+#             */
/*   Updated: 2019/06/04 16:27:56 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_ntab(char **tab)
{
	int		i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		ft_memdel((void*)&(tab[i]));
	ft_memdel((void*)&tab);
}
