/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:16 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:18 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_strlen_char(const char *line, char c)
{
	unsigned int	i;

	i = 0;
	while (line && line[i] && line[i] != c && line[i] != '\0')
		i++;
	return (i);
}
