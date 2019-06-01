#include "cmd_parsing.h"

//Move ?
static t_bool	is_env_var_name_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/*
** get_var_name
** parse the string while(is_env_var_name_char)
** return (NULL) if name length == 0;
** return the allocated var_name otherwise
*/

//Move ?
char			*get_var_name(char *str)
{
	size_t		i;
	char	*var_name;

	str++;
	i = 0;
	while (str[i] && is_env_var_name_char(str[i]))//should i check $$ ?
		i++;
	if (i == 0)
		return (NULL);
	if (!(var_name = ft_strndup(str, i)))
		ERROR_MEM;
	return (var_name);
}

/*
** substitute_env_var //NO MORE
** realloc and return a new string with expanded variable
** set the index 'i' accordingly
** free (old_str && var_name)
*/

//could be more generic with a parameter 'trim_size', "$((" would be 5
void	substitute_env_var(char **str, size_t *i, const char *var_name
			, t_vars *vars)
{
	const char	*var_value;
	size_t	index[2];

	if (!(var_value = get_envline_value((char *)var_name, vars->env_vars)))
		var_value = &var_name[ft_strlen(var_name)];//toujours aussi degueu
	index[0] = *i;
	index[1] = *i + ft_strlen(var_name) + 0;
	substitute_slice(str, index, var_value);
	*i += ft_strlen(var_value) - 1;
	ft_strdel((char**)&var_name);
}

//USELESS
/*
t_bool		parse_env_var(char **str, t_vars *vars)
{
	size_t		i;
	t_bool		escaped;
	const char	*var_name;

	ft_printf("IN PARSE_ENV_VAR\n");
	i = 0;
	escaped = 0;
	while ((*str)[i])
	{
		if (!escaped && (*str)[i] == '$' && ft_strncmp("$((", (*str) + i,
					3))//TODO remove strncmp when both ${ and $ will be parse together
		{
			ft_printf("MATCH ON I=%ld\n", i);
			//get_var_name return NULL when get_var_name didn't find a name, ex: $\PWD
			if (!(var_name = get_var_name((*str) + i)))//test add + i
			{
				i++;
				continue ;
			}
			ft_printf("VAR_NAME|%s|\n", var_name);
			substitute_env_var(str, &i, var_name, vars);
			ft_printf("*str |%s|\n", *str);
		}
		else if ((*str)[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
			escaped = 0;
		i++;
	}
	return (1);
}
*/
