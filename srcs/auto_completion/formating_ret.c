/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formating_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:15 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:19 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int		format_finding_and_get_correct_ret(char **ret,
		int start_actual_word, char *input, unsigned int len)
{
	char	*save;
	char	*tmp;

	initialize_str(&save, &tmp, NULL, NULL);
	if (!(save = ft_strndup(input, start_actual_word)))
		clean_exit(1, 1);
	if (!(*ret))
	{
		if (!(*ret = ft_strndup(input, len)))
			clean_exit(1, 1);
	}
	else
	{
		if (save)
		{
			if (!(tmp = ft_strjoin(save, (*ret))))
				clean_exit(1, 1);
			ft_strdel(ret);
		}
		if (!((*ret) = ft_strdup(tmp)))
			clean_exit(1, 1);
		ft_strdel(&tmp);
	}
	ft_strdel(&save);
	return (0);
}
