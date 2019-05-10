#include "libft.h"
#include "line_editing.h"

char				*get_to_find_file(char *str)
{
	char			*to_find;
	int				len;
	int				count;

	to_find = NULL;
	len = ft_strlen(str) - 1;
	count = len;
	if (is_white_spaces(str[len]))
		return (NULL);
	while (len >= 0 && (!is_white_spaces(str[len])
				|| (len > 0 && is_white_spaces(str[len]) && str[len] == '\\')))
		--len;
	len++;
	if (is_white_spaces(str[len - 1]))
	{
		if (!(to_find = ft_strsub(str, len, count - len + 1)))
			return (NULL);
	}
	return (to_find);
}
