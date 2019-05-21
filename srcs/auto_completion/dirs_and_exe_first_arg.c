#include "libft.h"
#include "line_editing.h"

static int				find_matching_dirs_and_exe_even_hidden(char *directory, t_auto_comp **match, char *to_find)
{
	DIR					*dir;
	struct dirent		*ent;
	char				*tmp;
	char				*filename;

	if ((dir = opendir(directory)) == NULL)
		return (1);//ERR_OPENDIR
	while ((ent = readdir(dir)))
	{
		tmp = NULL;
		filename = NULL;
		if ((!to_find[0] || (!compare_entry(to_find, ent->d_name))) && ft_strncmp("..", ent->d_name, 3) && ft_strncmp(".", ent->d_name, 2))
		{
			if (!(filename = ft_strjoin(directory, ent->d_name)))
				ERROR_MEM
			if (access(filename, X_OK) == 0)
			{
				if (ent->d_type && ent->d_type == DT_DIR)
					tmp = ft_strjoin(ent->d_name, "/");
				else
					tmp = ft_strdup(ent->d_name);
				/*
				ft_putendl(tmp);
				sleep(1);
				*/
				if (create_match_link(match, tmp, -1))
				{
					closedir(dir);
					return (1);//ERR MALL
				}
				ft_strdel(&tmp);
			}
		}
	}
	if (closedir(dir) == -1)
		return (1);//ERR_CLOSEDIR;
	return (0);
}

char					*search_dirs_and_exe(char *str, int len)
{
	char				*ret_str;
	char				*ret_tmp;
	char				*to_find;
	char				*path;
	t_auto_comp			*match;

	ret_str = NULL;
	ret_tmp = NULL;
	path = NULL;
	match = NULL;
	to_find = NULL;
	if ((to_find = ft_strrchr(str, '/') + 1))
	{
		if (!(path = ft_strndup(str, ft_strlen(str) - ft_strlen(to_find))))
			return (NULL);
			//ERROR_MEM
	}
	else
		if (!(path = ft_strdup(str)))
			ERROR_MEM
		if (find_matching_dirs_and_exe_even_hidden(path, &match, to_find))
			ERROR_MEM
		if (match)
		{
			while (match->prev)
				match = match->prev;
			ret_tmp = get_ret_or_display_matches(match, to_find, len - ft_strlen(path));

			if (!(ret_str = ft_strjoin(path, ret_tmp)))
				ERROR_MEM
		}
	return (ret_str);
}
