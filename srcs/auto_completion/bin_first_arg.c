#include "libft.h"
#include "line_editing.h"

char				*new_auto_completion_bin(t_vars *vars, char *str, char *to_find_and_next_char, unsigned int len)
{
	char			**path;
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;
	int				i;

	match = NULL;
	ret_str = NULL;
	i = -1;
	path = NULL;
	if (get_path(&path, vars))//recup le path
		ERROR_MEM
	if (!(to_find = ft_strdup(str)))
		ERROR_MEM
	if (find_matching_exe(path, &match, to_find, to_find_and_next_char))//stock dans match les noms correspondants
				ERROR_MEM
	ft_free_ntab(path);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, len);//chercher alias
	if (to_find)
		ft_strdel(&to_find);
	return (ret_str);
	}
