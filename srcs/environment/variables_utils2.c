#include "ftsh.h"
#include "env.h"

/*
** get_varline_value
** return the allocated 'var_value' corresponding to the given var_name
*/

char	*get_varline_value(char *search, char **ntab)
{
	char	*varline;
	char	*var_value;
	int		i;

	if ((varline = get_varline_from_vartab(search, ntab)))
	{
		i = 0;
		while (varline[i] && varline[i] != '=')
			i++;
		if (varline[i] == '=')
		{
			if (!(var_value = ft_strdup(varline + i + 1)))
				clean_exit(1, MALLOC_ERR);
			return (var_value);
		}
	}
	return (NULL);
}

/*
** concat_for_vartab
** concatenate var_name and var_value
** to get "var_name=var_value"
** return the 'varline'
*/

char	*concat_for_vartab(char *var_name, char *var_value)
{
	size_t	name_len;
	size_t	value_len;
	char	*new_varline;

	name_len = ft_strlen(var_name);
	value_len = ft_strlen(var_value);
	if (!(new_varline = ft_strnew(name_len + value_len + 1)))
		clean_exit(1, MALLOC_ERR);
	ft_strcpy(new_varline, var_name);
	new_varline[name_len] = '=';
	ft_strcpy(&new_varline[name_len + 1], var_value);
	return (new_varline);
}
