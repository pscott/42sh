#include "expand.h"

/*
** is_matched
** check if the given expression is matched
** return 1 if '$((' is matched with a '))'
*/

t_bool	is_matched(const char *str
		, const char *begin_match, const char *end_match)
{
	size_t			i;
	unsigned int	braces_count;

	i = 0;
	braces_count = 0;
	while (str[i])
	{
		//if (!ft_strncmp("$((", &str[i], 3))
		if (!ft_strncmp(begin_match, &str[i], ft_strlen(begin_match)))
		{
			braces_count++;
			i += 2;
		}
		//else if (!ft_strncmp("))", $str[i], 2))
		else if (!ft_strncmp(end_match, &str[i], ft_strlen(end_match)))
		{
			braces_count--;
			i++;
			if (braces_count == 0)
				break ;
		}
		i++;
	}
	return ((braces_count) ? 0 : 1);
}
