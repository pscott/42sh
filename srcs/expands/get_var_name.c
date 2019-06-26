#include "cmd_parsing.h"

char	*get_var_name(char *str)
{
	size_t		i;
	char		*var_name;

	str++;
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0)
		return (NULL);
	if (!(var_name = ft_strndup(str, i)))
		clean_exit(1, MALLOC_ERR);
	return (var_name);
}

int		is_valid_varname(char *str)
{
	int	i;

	if (str[0] == '=' || ft_isdigit(str[0]))
		return (0);
	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}
