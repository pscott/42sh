/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ntab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:27:07 by pscott            #+#    #+#             */
/*   Updated: 2019/06/04 16:27:08 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_ntab(char **ntab)
{
	unsigned int i;

	i = 0;
	if (!ntab)
	{
		ft_putendl("(null)");
		return ;
	}
	while (ntab[i])
	{
		ft_putendl(ntab[i]);
		i++;
	}
}
