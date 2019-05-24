#include "libft.h"
#include "line_editing.h"

char				*new_auto_completion_bin
	(t_vars *vars, const char *str,
	 const char *to_find_and_next_char)
{
	char			**path;
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;

	match = NULL;
	ret_str = NULL;
	path = NULL;
	get_path(&path, vars);
	if (!(to_find = ft_strdup(str)))
		ERROR_MEM
	find_matching_exe(path, &match, to_find, to_find_and_next_char);
	if (path)
		ft_free_ntab(path);
	if (match)
		ret_str = get_ret_or_display_matches(match, to_find, ft_strlen(to_find));
	if (to_find)
		ft_strdel(&to_find);
	return (ret_str);
}
