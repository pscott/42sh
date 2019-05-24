/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:42:01 by aschoenh          #+#    #+#             */
/*   Updated: 2019/05/24 15:22:20 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_editing.h"

int				is_same_char(char a, char b)
{
	if (a == b)
		return (1);
	if (a <= 'Z' && a >= 'A' && a + 32 == b)
		return (1);
	if (a <= 'z' && a >= 'a' && a - 32 == b)
		return (1);
	return (0);
}

int				get_needed_values
	(const char *input, unsigned int len, char **str, char **to_find_full)
{
	int			start_actual_word;

	start_actual_word = len;
	*str = NULL;
	*to_find_full = NULL;
	if (!(*str = ft_strndup(input, len + 1)))
		ERROR_MEM
	if (!(*to_find_full = ft_strndup(input, len)))
		ERROR_MEM
	if (len > 0 && is_white_spaces((*to_find_full)[len - 1]))
		start_actual_word--;
	while (start_actual_word > 0 && !is_white_spaces((*to_find_full)[start_actual_word]))
		start_actual_word--;
	if (is_white_spaces((*to_find_full)[start_actual_word]))
		start_actual_word++;
	return (start_actual_word);
}

int				get_path(char ***path, t_vars *vars)
{
	char		*tmpath;

	if (!vars || !vars->env_vars)
		return (0);
	if (!(tmpath = get_envline_value("PATH", vars->env_vars)))
	{
		*path = NULL;
		return (0);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		ERROR_MEM
	return (0);
}

int				free_two_strings(char **s1, char **s2)
{
	if (s1)
		ft_strdel(s1);
	if (s2)
		ft_strdel(s2);
	return (0);
}

int				free_four_strings(char **s1, char **s2, char **s3, char **s4)
{
	free_two_strings(s1, s2);
	free_two_strings(s3, s4);
	return (0);
}
