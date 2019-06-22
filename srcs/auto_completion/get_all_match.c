#include "auto_completion.h"

int		get_all_match(char *directory, t_auto_comp **match,
		const char *to_find, const char *next)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);
	tmp = NULL;
	while ((ent = readdir(dir)))
		if (!(compare_entry(to_find, ent->d_name)))
		{
			if (check_if_slash(ent, directory, NULL))
				tmp = ft_strjoin(ent->d_name, "/");
			else if (next[ft_strlen(next) - 1]
				== to_find[ft_strlen(to_find) - 1])
				tmp = ft_strjoin(ent->d_name, " ");
			else
				tmp = ft_strdup(ent->d_name);
			if (!tmp)
				clean_exit(1, 1);
			create_match_link(match, tmp);
			ft_strdel(&tmp);
		}
	if (closedir(dir) == -1)
		return (1);
	return (0);
}
