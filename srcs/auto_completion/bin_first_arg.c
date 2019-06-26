/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_first_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:01:45 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/25 11:49:17 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char				*auto_completion_bin(t_vars *vars,
		const char *str, const char *to_find_and_next_char)
{
	char			**path;
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;

	match = NULL;
	ret_str = NULL;
	path = NULL;
	get_path(&path, vars);
	if (!(to_find = ft_strdup(str)))
		clean_exit(1, MALLOC_ERR);
	get_matching_exe(path, &match, to_find, to_find_and_next_char);
	if (path)
		ft_free_ntab(path);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find,
				ft_strlen(to_find), 0);
	if (to_find)
		ft_strdel(&to_find);
	return (ret_str);
}
