#include "auto_completion.h"

static int			find_matching_dirs(const char *directory,
					t_auto_comp **match, char *to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);
	tmp = NULL;
	while ((ent = readdir(dir)))
	{
		if (!to_find || !to_find[0] || !compare_entry(to_find, ent->d_name))
		{
			if (check_if_slash(ent, directory, NULL))
			{
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

char				*get_dirs_first_arg(const char *directory, const char *str,
					unsigned int len)
{
	t_auto_comp		*match;
	char			*ret_str;
	char			*to_find;

	match = NULL;
	ret_str = NULL;
	if (!(to_find = ft_strdup(str)))
		clean_exit(1, MALLOC_ERR);
	find_matching_dirs(directory, &match, to_find);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, len, 0);
	ft_strdel(&to_find);
	return (ret_str);
}
