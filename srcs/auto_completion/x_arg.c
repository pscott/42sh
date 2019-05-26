#include "libft.h"
#include "line_editing.h"
#include "errors.h"

int					find_all_match(char *directory, t_auto_comp **match,
		const char *to_find, const char *next)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		if (!(compare_entry(to_find, ent->d_name)))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
				tmp = ft_strjoin(ent->d_name, "/");
			else if (is_white_spaces(next[ft_strlen(to_find)]) || !next[ft_strlen(to_find)])
				tmp = ft_strjoin(ent->d_name, " ");
			else
				tmp = ft_strdup(ent->d_name);
			if (!tmp)
				ERROR_MEM
			create_match_link(match, tmp);
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

int					find_all_except_dots(const char *directory, t_auto_comp **match)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (0);
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		if (ft_strncmp("..", ent->d_name, 3) && ft_strncmp(".", ent->d_name, 2))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
				tmp = ft_strjoin(ent->d_name, "/");
			else
				tmp = ft_strjoin(ent->d_name, " ");
			if (!tmp)
				ERROR_MEM
			create_match_link(match, tmp);
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

char				*handle_x_arg(const char *input, const char *to_find_and_next_char)
{
	char			*path;
	char			*to_find;
	char			*tmp;
	char			*ret_str;
	t_auto_comp		*match;

	to_find = NULL;
	path = NULL;
	ret_str = NULL;
	match = NULL;
	tmp = NULL;

	if (input && input[0] == '~' && (!input[1] || input[1] != '/'))
		return (ret_str = users_passwd(input));
	if (input && input[0] && ft_strchr(input, '/'))
		tmp = ft_strndup(input, ft_strlen(input) - ft_strlen(ft_strrchr(input, '/') + 1));
	get_path_file_and_to_find(input, &path, &to_find);
	if (!to_find[0] || is_white_spaces(to_find[0]))
		find_all_except_dots(path, &match);
	else
		find_all_match(path, &match, to_find, to_find_and_next_char);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	else if (!(ret_str = ft_strdup(to_find)))
		ERROR_MEM
			free_four_strings(&tmp, &ret_str, &path, &to_find);
	return (ret_str);
}
