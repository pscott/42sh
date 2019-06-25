#include "auto_completion.h"

static int			find_matching_home_dirs(const char *directory,
					t_auto_comp **match, const char *to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);
	while ((ent = readdir(dir)))
	{
		if ((!to_find || !to_find[0] || !compare_entry(to_find, ent->d_name))
				&& (ft_strncmp("..", ent->d_name, 3)
				&& ft_strncmp(".", ent->d_name, 2)))
		{
			if (check_if_slash(ent, directory, NULL))
			{
				tmp = NULL;
				tmp = ft_strjoin(ent->d_name, "/");
				create_match_link(match, tmp);
				ft_strdel(&tmp);
			}
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

static char			*search_dirs_home_first_arg(const char *directory,
					const char *str)
{
	t_auto_comp		*match;
	char			*ret_str;
	char			*to_find;

	match = NULL;
	ret_str = NULL;
	if (!(to_find = ft_strdup(str)))
		clean_exit(1, MALLOC_ERR);
	if (find_matching_home_dirs(directory, &match, to_find))
		return (to_find);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find,
				ft_strlen(to_find), 0);
	ft_strdel(&to_find);
	return (ret_str);
}

char				*home_directory_first_arg(const char *to_find)
{
	char			*ret_str;
	char			*path;
	char			*tmp2;
	char			*tmp;

	ret_str = NULL;
	path = NULL;
	tmp = NULL;
	tmp2 = NULL;
	if (to_find && to_find[0] && ft_strchr(to_find, '/'))
		if (!(tmp2 = ft_strndup(to_find, ft_strlen(to_find)
				- ft_strlen(ft_strrchr(to_find, '/') + 1))))
			clean_exit(1, MALLOC_ERR);
	get_path_file_and_to_find((char *)to_find, &path, &tmp);
	ret_str = search_dirs_home_first_arg(path, tmp);
	ft_strdel(&tmp);
	if (!(tmp = ft_strjoin(tmp2, ret_str)))
		clean_exit(1, MALLOC_ERR);
	ft_strdel(&path);
	ft_strdel(&ret_str);
	ft_strdel(&tmp2);
	return (tmp);
}
