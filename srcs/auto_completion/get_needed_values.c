#include "auto_completion.h"
#include "env.h"

static int		get_start_cmd_index(const char *str, int len)
{
	while (str && len >= 0)
	{
		if ((str[len] == '&' || str[len] == ';' || str[len] == '|')
				&& (len == 0 || str[len - 1] != '\\'))
			return (len + 1);
		len--;
	}
	return (0);
}

int				get_needed_values
	(const char *input, unsigned int len, char **str, char **to_f)
{
	int			start;
	int			start_cmd;

	*str = NULL;
	*to_f = NULL;
	start_cmd = get_start_cmd_index(input, len - 1);
	if (!(*str = ft_strndup(input + start_cmd, len + 1 - start_cmd)))
		clean_exit(1, MALLOC_ERR);
	if (!(*to_f = ft_strndup(input + start_cmd, len - start_cmd)))
		clean_exit(1, MALLOC_ERR);
	start = len - start_cmd;
	while (start > 0
		&& !ft_is_unslashed_metachar(*to_f, start, white_space)
		&& (((*to_f)[start] != '\'' && ((*to_f)[start] != '\"'))
			&& (*to_f)[start] != '\\'))
		start--;
	while (ft_is_unslashed_metachar(*to_f, start, white_space)
		|| (start == 0
		&& ((ft_is_white_space((*to_f)[start])) || ft_is_quote((*to_f)[start])))
		|| (((*to_f)[start] == '\'' || ((*to_f)[start] == '\"'))
			&& (*to_f)[start] != '\\'))
		start++;
	return (start);
}

int				when_to_start(char *str, char **to_f)
{
	int			i;

	i = 0;
	while (str && ft_is_white_space(str[i]))
		i++;
	i++;
	if (str && str[i] == '{')
		i++;
	if (!(*to_f = ft_strdup(str + i)))
		clean_exit(1, MALLOC_ERR);
	return (i);
}
