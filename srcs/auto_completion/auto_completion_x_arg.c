#include "auto_completion.h"
#include "errors.h"

static int			find_all_except_dots(const char *directory,
					t_auto_comp **match)
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
			if (check_if_slash(ent, directory, NULL))
				tmp = ft_strjoin(ent->d_name, "/");
			else
				tmp = ft_strjoin(ent->d_name, " ");
			if (!tmp)
				clean_exit(1, 1);
			create_match_link(match, tmp);
			ft_strdel(&tmp);
		}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

void				get_good_ret_str(char **ret_str, char *tmp)
{
	char			*tmp2;

	tmp2 = NULL;
	if (!(tmp2 = ft_strjoin(tmp, *ret_str)))
		clean_exit(1, 1);
	ft_strdel(ret_str);
	*ret_str = tmp2;
}

char				*auto_completion_x_arg(char *input,
					const char *to_f_and_next_char)
{
	char			*path;
	char			*to_f;
	char			*tmp;
	char			*r_str;
	t_auto_comp		*match;

	initialize_str(&to_f, &path, &r_str, &tmp);
	match = NULL;
	if (input && input[0] == '~' && (!input[1] || input[1] != '/'))
		return (r_str = users_passwd(input));
	else if (input && input[0] && ft_strchr(input, '/'))
		tmp = ft_strndup(input, ft_strlen(input)
			- ft_strlen(ft_strrchr(input, '/') + 1));
	get_path_file_and_to_find(input, &path, &to_f);
	if (to_f && (!to_f[0] || ft_is_white_space(to_f[0])))
		find_all_except_dots(path, &match);
	else
		get_all_match(path, &match, to_f, to_f_and_next_char);
	if (match)
		r_str = get_ret_or_display_matches(match, to_f, ft_strlen(to_f), 0);
	else if (to_f && !(r_str = ft_strdup(to_f)))
		clean_exit(1, 1);
	get_good_ret_str(&r_str, tmp);
	free_four_strings(&tmp, NULL, &path, &to_f);
	return (r_str);
}
