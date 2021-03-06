/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_first_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:01:46 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/25 12:30:53 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int					get_everything_from_path(char *path, t_auto_comp **match)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(path)) == NULL)
		return (1);
	while ((ent = readdir(dir)))
	{
		if (ft_strncmp(ent->d_name, "..", 2) && ft_strncmp(ent->d_name, ".", 1))
		{
			tmp = ft_strdup(ent->d_name);
			create_match_link(match, tmp);
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

int					find_exe_space(char **path, t_auto_comp **match)
{
	int				i;
	char			*true_path;

	true_path = NULL;
	i = 0;
	while (path && path[i])
	{
		true_path = rm_spaces_path(path[i++]);
		get_everything_from_path(true_path, match);
		ft_strdel(&true_path);
	}
	return (0);
}

int					find_all_var_and_exe(char **path, t_auto_comp **match)
{
	find_exe_space(path, match);
	return (0);
}

char				*auto_completion_space(t_vars *vars)
{
	char			**path;
	t_auto_comp		*match;

	path = NULL;
	match = NULL;
	get_path(&path, vars);
	find_all_var_and_exe(path, &match);
	add_builtins(&match, "", "", 0);
	if (path)
		ft_free_ntab(path);
	if (match)
		get_ret_or_display_matches(match, NULL, 0, 0);
	return (NULL);
}
