//#include "42sh.h"
//#include "lexer.h"
#include "cmd_parsing.h"

//*i is index[0]
static void			substitute_param(char **str, size_t *i
					, const char *var_name, t_vars *vars)
{
	const char	*var_value;
	size_t		index[2];
	
	if (!(var_value = get_envline_value((char *)var_name, vars->env_vars)))
		var_value = &var_name[ft_strlen(var_name)];//toujours aussi degueu
	index[0] = *i;
	index[1] = *i + ft_strlen(var_name) + 2;
	*i += ft_strlen(var_value) - 1;
	substitute_slice(str, index, var_value);
	ft_strdel((char**)&var_name);
}

static const char	*get_param_sub_name(const char *str)
{
	size_t	i;

	i = 1;
	while (str[++i] && str[i] != '}')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: bad substitution\n"
				, SHELL_NAME, str);
			return (NULL);
		}
	}
	if (str[i] == '}')//check me
		return (ft_strndup(&str[2], i - 2));
	return (NULL);
}

//TODO rename parse_vars
t_bool				parse_param_sub(char **str, t_vars *vars)
{
	size_t		i;
	t_bool		escaped;
	const char	*var_name;

	i = 0;
	escaped = 0;
	while ((*str)[i])
	{
		if (!escaped && !ft_strncmp("${", (*str) + i, 2)
				&& is_terminated("${", "}", (*str) + i))
		{
			if (!(var_name = get_param_sub_name((*str) + i)))//this print 'bad sub'
				return (0);
			substitute_param(str, &i, var_name, vars);
		}
		else if (!escaped && (*str)[i] == '$'
				&& (var_name = get_var_name((*str) + i)))
			substitute_env_var(str, &i, var_name, vars);
		else if ((*str)[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
			escaped = 0;
		i++;
	}
	return (1);
}
