/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:01:46 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/18 18:51:50 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"
#include "env.h"

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
		clean_exit(1, 1);
	if (!(*to_find_full = ft_strndup(input, len)))
		clean_exit(1, 1);
	if (len > 0
		&& ft_is_unslashed_metachar(*to_find_full, len - 1, white_space))
		start_actual_word--;
	while (start_actual_word > 0
		&& !ft_is_unslashed_metachar(*to_find_full,
			start_actual_word, white_space))
		start_actual_word--;
	if (ft_is_unslashed_metachar(*to_find_full, start_actual_word, white_space))
		start_actual_word++;
	ft_dprintf(2, "{%d}", start_actual_word);
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
		return (1);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		clean_exit(1, 1);
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
