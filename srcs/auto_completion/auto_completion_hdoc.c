#include "errors.h"
#include "auto_completion.h"

static int			get_all(const char *directory,
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
			if (ent->d_type && ent->d_type == DT_DIR)
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

static char			*get_match_and_display_hdoc(const char *input,
					const char *to_find_and_next_char)
{
	char			*path;
	char			*to_find;
	char			*tmp;
	char			*r_str;
	t_auto_comp		*match;

	initialize_str(&to_find, &path, &r_str, &tmp);
	match = NULL;
	if (input && input[0] == '~' && (!input[1] || input[1] != '/'))
		return (r_str = users_passwd(input));
	else if (input && input[0] && ft_strchr(input, '/'))
		tmp = ft_strndup(input, ft_strlen(input)
				- ft_strlen(ft_strrchr(input, '/') + 1));
	get_path_file_and_to_find(input, &path, &to_find);
	if (!to_find[0])
		get_all(path, &match);
	get_all_match(path, &match, to_find, to_find_and_next_char);
	if (match)
		r_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	else if (!(r_str = ft_strdup(to_find)))
		clean_exit(1, 1);
	get_good_ret_str(&r_str, tmp);
	free_four_strings(&tmp, NULL, &path, &to_find);
	return (r_str);
}

char				*auto_completion_hdoc(char *input, unsigned int len)
{
	char			*to_find_full;
	char			*ret;
	char			*tmp;
	char			*str;
	int				start_actual_word;

	ret = NULL;
	tmp = NULL;
	if (!input)
		return (NULL);
	start_actual_word = get_needed_values(input, len, &str, &to_find_full);
	ret = get_match_and_display_hdoc(to_find_full + start_actual_word,
			str + start_actual_word);
	format_finding_and_get_correct_ret(&ret, start_actual_word, input, len);
	free_two_strings(&to_find_full, &str);
	return (ret);
}
