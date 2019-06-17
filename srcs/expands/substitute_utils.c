#include "ftsh.h"
#include "cmd_parsing.h"

int		is_terminated(const char *open_pattern,
	const char *close_pattern, const char *str)
{
	size_t	i;
	size_t	close_len;

	i = open_pattern ? ft_strlen(open_pattern) : 0;
	if (i > ft_strlen(str))
		return (0);
	close_len = ft_strlen(close_pattern);
	while (str[i])
	{
		if (!(ft_strncmp(close_pattern, str + i, close_len)))
			return (1);
		i++;
	}
	return (0);
}

/*
** is_matched
** check if the given expression is matched
** return 1 if '$((' is matched with a '))'
*/

int		is_matched(const char *str, const char *begin_match,
	const char *end_match)
{
	size_t			i;
	unsigned int	braces_count;

	i = 0;
	braces_count = 0;
	while (str[i])
	{
		if (!ft_strncmp(begin_match, &str[i], ft_strlen(begin_match)))
		{
			braces_count++;
			i += ft_strlen(begin_match) - 1;
		}
		else if (!ft_strncmp(end_match, &str[i], ft_strlen(end_match)))
		{
			braces_count--;
			i += ft_strlen(end_match) - 1;
			if (braces_count == 0)
				break ;
		}
		i++;
	}
	return ((braces_count) ? 0 : 1);
}

/*
** substitute_slice
** replace old_str from index[0] to index [1] by to_sub
**
** 		aaa$USER/aaa
** 		   ^   ^
**   index[0,  1]
**
**	=   aaaMichel/aaa
*/

int		substitute_slice(char **old_str, size_t index[2], const char *to_sub)
{
	size_t	new_len;
	size_t	to_sub_len;
	char	*new_str;

	to_sub_len = ft_strlen(to_sub);
	new_len = ft_strlen(*old_str) + to_sub_len - (index[1] - index[0]);
	if (!(new_str = ft_strnew(new_len + 1)))
		clean_exit(1, 1);
	ft_strncpy(new_str, *old_str, index[0]);
	ft_strncpy(&new_str[index[0]], to_sub, to_sub_len);
	ft_strncpy(&new_str[ft_strlen(new_str)], (*old_str) + index[1] + 1
			, ft_strlen((*old_str) + index[1] + 1));
	ft_strdel(old_str);
	ft_dprintf(2, "new str|%s|\n", new_str);
	*old_str = new_str;
	return (1);
}

void	substitute_cmd_value(char **str, size_t *i, t_vars *vars)
{
	char	*nb_str;
	size_t	index[2];

	if (!(nb_str = ft_itoa(vars->cmd_value)))
		clean_exit(1, 1);
	index[0] = *i;
	index[1] = *i + 1;
	substitute_slice(str, index, nb_str);
	ft_strdel(&nb_str);
}

int		set_escaped(int escaped, char c)
{
	if (c == '\\')
		escaped = (escaped) ? 0 : 1;
	else
		escaped = 0;
	return (escaped);
}
