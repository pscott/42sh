#include "libft.h"
#include "line_editing.h"

int					find_matching_dirs(char *directory, t_auto_comp **match, char * to_find)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if ((dir = opendir(directory)) == NULL)
		return (1);//ERR_OPENDIR
	while ((ent = readdir(dir)))
	{
		if (!compare_entry(to_find, ent->d_name))
		{
			if (ent->d_type && ent->d_type == DT_DIR)
			{
				tmp = NULL;
				tmp = ft_strjoin(ent->d_name, "/");
				if (create_match_link(match, tmp, -1))
				{
					closedir(dir);
					return (1);//ERR MALL
				}
			}
		}
	}
	if (closedir(dir) == -1)
		return (1);//ERR_CLOSEDIR;
	return (0);
}

char				*search_dirs_first_arg(char *directory, char *str, int len)
{
	t_auto_comp		*match;
	char			*ret_str;
	char			*to_find;

	match = NULL;
	ret_str = NULL;
	if (!(to_find = ft_strdup(str)))
		ERROR_MEM
	if (find_matching_dirs(directory, &match, to_find))//je fais la liste de match avec / append
		ERROR_MEM
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, len);
	ft_strdel(&to_find);
	return (ret_str);
}
