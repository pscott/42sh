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
			else if (ft_is_white_space(next[ft_strlen(to_find)]) || !next[ft_strlen(to_find)])
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
