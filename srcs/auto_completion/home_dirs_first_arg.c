#include "libft.h"
#include "line_editing.h"

static int		find_matching_home_dirs(const char *directory, t_auto_comp **match, const char * to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);//ERR_OPENDIR
	while ((ent = readdir(dir)))
	{
		if ((!to_find || !to_find[0] || !compare_entry(to_find, ent->d_name))
				&& (ft_strncmp("..", ent->d_name, 3)
				&& ft_strncmp(".", ent->d_name, 2)))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
			{
				tmp = NULL;
				tmp = ft_strjoin(ent->d_name, "/");
				create_match_link(match, tmp);
				ft_strdel(&tmp);
			}
		}
	}
	if (closedir(dir) == -1)
		return (1);//ERR_CLOSEDIR;
	return (0);
}

static char			*search_dirs_home_first_arg(const char *directory, const char *str)
{
	t_auto_comp		*match;
	char			*ret_str;
	char			*to_find;

	match = NULL;
	ret_str = NULL;
	if (!(to_find = ft_strdup(str)))
		ERROR_MEM
	if (find_matching_home_dirs(directory, &match, to_find))//je fais la liste de match avec / append
		ERROR_MEM
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
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
		if (!(tmp2 = ft_strndup(to_find, ft_strlen(to_find) - ft_strlen(ft_strrchr(to_find, '/') + 1))))
			ERROR_MEM
	get_path_file_and_to_find(to_find, &path, &tmp);
	ret_str = search_dirs_home_first_arg(path, tmp);
	ft_strdel(&tmp);
	if (!(tmp = ft_strjoin(tmp2, ret_str)))
		ERROR_MEM
	ft_strdel(&path);
	ft_strdel(&ret_str);
	ft_strdel(&tmp2);
	return (tmp);
}