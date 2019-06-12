/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_ntab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:16 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:18 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_dup_ntab(const char **tab)
{
	char	**new_tab;
	int		tab_len;
	int		i;

	if (!tab || !*tab)
		return (NULL);
	tab_len = ft_ntab_len(tab);
	if (!(new_tab = (char**)malloc((sizeof(char*) * (tab_len + 1)))))
		return (NULL);
	i = -1;
	while (++i < tab_len)
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
		{
			ft_free_ntab(new_tab);
			return (NULL);
		}
	}
	new_tab[i] = NULL;
	return (new_tab);
}
