#include "42sh.h"
#include "expand.h"

/*
** substitute_slice
** replace old_str from index[0] to index [1] by to_sub
**
** 		aaa$USER/aaa
** 		   ^    ^
** index  [0    1]
**		aaajean-luc de la rue/aaa
*/

t_bool	substitute_slice(char **old_str, size_t index[2], const char *to_sub)
{
	size_t	new_len;
	size_t	to_sub_len;
	char	*new_str;

	to_sub_len = ft_strlen(to_sub);
	new_len = ft_strlen(*old_str)
		+ to_sub_len
		- (index[1] - index[0]);
	if (!(new_str = ft_strnew(new_len)))
		ERROR_MEM;
	ft_strncpy(new_str, *old_str, index[0]);
	ft_strncpy(&new_str[index[0]], to_sub, to_sub_len);
	//ft_strncpy(&new_str[ft_strlen(new_str)], &old_str[index[1]],
	//		ft_strlen(&old_str[index[1]]));
	ft_strncpy(&new_str[ft_strlen(new_str)], (*old_str) + index[1],
			ft_strlen((*old_str) + index[1]));
	ft_strdel(old_str);
	*old_str = new_str;
	return (1);
}
