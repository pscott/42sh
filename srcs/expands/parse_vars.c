#include "cmd_parsing.h"
#include "env.h"

static void			substitute_env_var(char **str, size_t *i,
	const char *var_name, t_vars *vars)
{
	const char	*var_value;
	size_t		index[2];
	char		empty_char;

	empty_char = 0;
	//if (!(var_value = get_envline_value((char *)var_name, vars->shell_vars)))
	//{
	//	ft_dprintf(2, "NO VALUE\n");
	//	var_value = &empty_char;
	//}
	var_value = get_varline_value((char*)var_name, vars->shell_vars);//test
	ft_dprintf(2, "VALUE|%s|\n", var_value);
	index[0] = *i;
	index[1] = *i + ft_strlen(var_name) + 0;
	substitute_slice(str, index, var_value);
	*i += ft_strlen(var_value) - 1;
	ft_strdel((char**)&var_name);
	ft_strdel((char**)&var_value);
}

static void			substitute_param(char **str, size_t *i,
	const char *var_name, t_vars *vars)
{
	const char	*var_value;
	size_t		index[2];
	char		empty_char;

	if (!ft_strncmp(var_name, "?", 2))
	{
		if (!(var_value = ft_itoa(vars->cmd_value)))
			clean_exit(1, 1);
	}
	else
	{
		empty_char = 0;
		if (!(var_value = get_envline_value((char *)var_name, vars->shell_vars)))
			var_value = &empty_char;
	}
	index[0] = *i;
	index[1] = *i + ft_strlen(var_name) + 2;
	*i += ft_strlen(var_value) - 1;
	substitute_slice(str, index, var_value);
	ft_strdel((char**)&var_value);
	ft_strdel((char**)&var_name);
}

static const char	*bad_substitution(const char *str, t_vars *vars)
{
	if (vars->verbose)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: bad substitution\n",
			SHELL_NAME, str);
	}
	return (NULL);
}

static const char	*get_param_sub_name(const char *str, t_vars *vars)
{
	size_t		i;
	const char	*var_name;

	i = 1;
	if (!ft_strncmp(str, "${?}", 4))
	{
		if (!(var_name = ft_strdup("?")))
			clean_exit(1, 1);
		return (var_name);
	}
	while (str[++i] && str[i] != '}')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (bad_substitution(str, vars));
	}
	if (i == 2 && str[i] == '}')
		return (bad_substitution(str, vars));
	if (str[i] == '}')
	{
		if (!(var_name = ft_strndup(&str[2], i - 2)))
			clean_exit(1, 1);
		return (var_name);
	}
	return (NULL);
}

/*
** parse_vars
** look through **str, to find '${' or '$'
** return 1 on bad substitution with ${}
** return 0 otherwise
*/

int					parse_vars(char **str, t_vars *vars)
{
	size_t		i;
	int			escaped;
	const char	*var_name;

	i = 0;
	escaped = 0;
	while ((*str)[i])
	{
		if (!escaped && !ft_strncmp("${", (*str) + i, 2)
				&& is_terminated("${", "}", (*str) + i))
		{
			if (!(var_name = get_param_sub_name((*str) + i, vars)))
				return (1);
			substitute_param(str, &i, var_name, vars);
		}
		else if (!escaped && !ft_strncmp("$?", (*str) + i, 2))
			substitute_cmd_value(str, &i, vars);
		else if (!escaped && (*str)[i] == '$'
				&& (var_name = get_var_name((*str) + i)))
			substitute_env_var(str, &i, var_name, vars);
		else
			escaped = set_escaped(escaped, (*str)[i]);
		i++;
	}
	return (0);
}
