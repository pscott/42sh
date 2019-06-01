#include "42sh.h"
#include "cmd_parsing.h"

//is_terminated doesn't care about '\' escape
t_bool	is_terminated(const char *open, const char *closed, const char *str)
{
	size_t	i;

	i = open ? ft_strlen(open) : 0;
	if (i > ft_strlen(str))
		return (0);
	while (str[i])
	{
		if (!ft_strncmp(closed, str + i, ft_strlen(closed)))
			return (1);
		i++;
	}
	return (0);
}

/*
** substitute_slice
** replace old_str from index[0] to index [1] by to_sub
**
** 		aaa$USER/aaa
** 		   ^    ^
** index  [0,   1]
**		aaaNEWVAR/aaa
**		  
** Should be:
** 		aaa$USER/aaa
**         ^   ^
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
	if (!(new_str = ft_strnew(new_len + 1)))
		ERROR_MEM;
	ft_strncpy(new_str, *old_str, index[0]);
	ft_strncpy(&new_str[index[0]], to_sub, to_sub_len);
	ft_strncpy(&new_str[ft_strlen(new_str)], (*old_str) + index[1] + 1,
			ft_strlen((*old_str) + index[1] + 1));//-1 test
	ft_strdel(old_str);
	*old_str = new_str;
	return (1);
}

//	${USER}
//	^      ^

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
	ft_printf("braces_count = %u, in |%s|\n", braces_count, str);
	return ((braces_count) ? 0 : 1);
}
