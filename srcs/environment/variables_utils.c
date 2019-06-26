#include "ftsh.h"
#include "env.h"
#include "hashmap.h"

/*
** add_varline
** add (or replace if var_name already exist) to the given ntab
*/

void	add_varline(char *varline, char ***ntab)
{
	char	*var_name;
	char	*var_value;
	t_vars	*vars;

	vars = get_vars(NULL);
	if ((var_name = get_varline_name(varline)))
	{
		if (!(var_value = ft_strdup(varline + ft_strlen(var_name) + 1)))
			clean_exit(1, MALLOC_ERR);
		add_variables(var_name, var_value, ntab);
		ft_strdel(&var_name);
		ft_strdel(&var_value);
	}
	else
		*ntab = append_line_to_ntab(varline, *ntab);
}

/*
** add_variables
** add or replace the varline corresponding to 'var_name=var_value;
*/

void	add_variables(char *var_name, char *var_value, char ***ntab)
{
	char	*new_str;
	int		i;
	t_vars	*vars;

	vars = get_vars(NULL);
	i = get_envline_index(var_name, *ntab);
	if (!(ft_strcmp("PATH", var_name)))
		reset_hashmap(&vars->hashmap);
	new_str = concat_for_vartab(var_name, var_value);
	if (i >= 0)
	{
		ft_strdel(&(*ntab)[i]);
		(*ntab)[i] = new_str;
	}
	else
	{
		*ntab = append_line_to_ntab(new_str, *ntab);
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
	unsigned int	search_len;

	search_len = ft_strlen(search);
	if (ft_strncmp(search, varline, search_len) == 0
		&& varline[search_len] == '=')
		return (search_len + 1);
	return (0);
}

/*
** get_varline_from_vartab
** return the varline corresponding to 'search'
** it is NOT allocated
** return NULL if not found
*/

char	*get_varline_from_vartab(char *search, char **ntab)
{
	unsigned int	i;

	if (!search || !ntab)
		return (NULL);
	i = 0;
	while (ntab[i])
	{
		if (str_equ_varname(search, ntab[i]))
			return (ntab[i]);
		i++;
	}
	return (NULL);
}

char	*get_varline_name(char *varline)
{
	int		i;
	char	*var_name;

	i = 0;
	while (varline[i] && varline[i] != '=')
		i++;
	if (varline[i] == '=')
	{
		if (!(var_name = ft_strndup(varline, i)))
			clean_exit(1, MALLOC_ERR);
		return (var_name);
	}
	return (NULL);
}
