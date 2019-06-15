#include "ftsh.sh"

/*
** add_variables
** add or replace the varline corresponding to 'var_name=var_value;
*/

void	add_variables(char *var_name, char *var_value, char ***tab)
{
	char	*new_str;
	char	*old_str;
	int		i;
	
	i = get_enline_index(var_name, *tab);
	new_str = concat_for_vartab(var_name, var_value);
	if (i >= 0)
	{
		ft_strdel((*tab)[i]);
		(*tab)[i] = new_str;
	}
	else
	{
		*tab = append_line_to_ntab(new_str, *tab);
		ft_strdel(&new_str);
	}
}

/*
** str_equ_varname
** compare 2 string until the first '='
** return 0 or '=' index
*/

int		str_equ_varname(char *search, char *varline)
{
	unsigned int	i;
	unsigned int	search_len;

	i = 0;
	search_len = ft_strlen(search);
	while (search[i] && varline[i] && search[i] == varline[i])
	{
		if (search[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

/*
** get_varline_from_vartab
** return the varline corresponding to 'search'
** return NULL if not found
*/

char	*get_varline_from_vartab(char *search, char **tab)
{
	unsigned int	i;

	if (!search || !env)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (str_equ_varname(search, tab[i]))
			return (tab[i]);
		i++;
	}
	return (NULL);
}

char	*get_varline_value(char *search, char **tab)
{
	char	*varline;
	char	*var_value;

	if (varline = get_varline_from_vartab(search, tab))
	{
		while (varline[i] && varline[i] != '=')
			i++;
		if (varline[i] == '=')
		{
			if (!(var_value = ft_strdup(var_line + i + 1)))
				clean_exit(1, 1);
			return (var_value);
		}
	}
	return (NULL);
}

char	*concat_for_vartab(char *var_name, char *var_value)
{
	size_t	name_len;
	size_t	value_len;
	char	*new_varline;

	name_len = ft_strlen(var_name);
	value_len = ft_strlen(var_value);
	if (!(new_varline = ft_strnew(name_len + value_len + 1)))
		clean_exit(1, 1);
	ft_strcpy(new_varline, var_name);
	new_varline[name_len] = '=';
	ft_strcpy(&new_varline[name_len + 1], var_value);
	return (new_varline);
}
