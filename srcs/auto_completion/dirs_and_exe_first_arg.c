#include "auto_completion.h"

int						check_if_slash(struct dirent *ent,
	const char *directory, const char *filename)
{
	char			buf[3];
	char			*tmp;
	int				ret;

	ret = 0;
	if (ent->d_type && ent->d_type == DT_DIR)
		++ret;
	else if (ent->d_type && ent->d_type == DT_LNK)
	{
		if (filename)
		{
			if (!(tmp = ft_strdup(filename)))
				clean_exit(1, 1);
		}
		else
		{
			if (!(tmp = ft_strjoin(directory, ent->d_name)))
				clean_exit(1, 1);
		}
		if (readlink(tmp, buf, 2))
			++ret;
		ft_strdel(&tmp);
	}
	return (ret);
}

static int				get_needed_values_to_create_match_link
	(char **tmp, struct dirent *ent, const char *directory)
{
	char			*filename;

	if (!(filename = ft_strjoin(directory, ent->d_name)))
		clean_exit(1, 1);
	if (access(filename, X_OK) == 0)
	{
		if (check_if_slash(ent, directory, filename))
			*tmp = ft_strjoin(ent->d_name, "/");
		else
			*tmp = ft_strdup(ent->d_name);
		if (!(*tmp))
			clean_exit(1, 1);
		ft_strdel(&filename);
		return (0);
	}
	ft_strdel(&filename);
	return (1);
}

static int				find_matching_dirs_and_exe_even_hidden
	(const char *directory, t_auto_comp **match, const char *to_find)
{
	DIR					*dir;
	struct dirent		*ent;
	char				*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		if ((!to_find[0] || (!compare_entry(to_find, ent->d_name)))
			&& ft_strncmp("..", ent->d_name, 3)
			&& ft_strncmp(".", ent->d_name, 2))
			if (!get_needed_values_to_create_match_link(&tmp, ent, directory))
			{
				create_match_link(match, tmp);
				ft_strdel(&tmp);
			}
	}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}

static int				get_path_and_to_find_local
	(char **to_find, char **path, const char *str)
{
	if ((*to_find = ft_strrchr(str, '/') + 1))
	{
		if (!(*path = ft_strndup(str, ft_strlen(str) - ft_strlen(*to_find))))
			clean_exit(1, 1);
	}
	else if (!(*path = ft_strdup(str)))
		clean_exit(1, 1);
	return (0);
}

char					*search_dirs_and_exe(const char *str)
{
	char				*ret_str;
	char				*ret_tmp;
	char				*to_find;
	char				*path;
	t_auto_comp			*match;

	initialize_str(&ret_str, &ret_tmp, &path, &to_find);
	match = NULL;
	get_path_and_to_find_local(&to_find, &path, str);
	if (!find_matching_dirs_and_exe_even_hidden(path, &match, to_find)
		&& match)
	{
		while (match->prev)
			match = match->prev;
		ret_tmp = get_ret_or_display_matches(match, to_find,
				ft_strlen(to_find));
		if (!(ret_str = ft_strjoin(path, ret_tmp)))
			clean_exit(1, 1);
		ft_strdel(&ret_tmp);
	}
	ft_strdel(&path);
	return (ret_str);
}
