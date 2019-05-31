#include "cmd_parsing.h"

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
static void	substitute_env_var(t_token *token, size_t *i, const char *var_name
			, t_vars *vars)
{
	const char	*var_value;
	size_t	index[2];

	if (!(var_value = get_envline_value((char *)var_name, vars->env_vars)))
		var_value = &var_name[ft_strlen(var_name)];//toujours aussi degueu
	index[0] = *i;
	index[1] = *i + ft_strlen(var_name) + 1;
	ft_printf("var_value: %s\n", var_value);//HEREHERE
	substitute_slice(&token->content, index, var_value);
	ft_printf("content: |%s|\n", token->content);
	*i += ft_strlen(var_value);
	ft_strdel((char**)&var_name);
}

t_bool		parse_env_var(t_token *token, t_vars *vars)
{
	size_t		i;
	t_bool		escaped;
	const char	*var_name;

	i = 0;
	escaped = 0;
	while (token->content[i])
	{
		if (!escaped && token->content[i] == '$')
		{
			//get_var_name return NULL when get_var_name didn't find a name, ex: $\PWD
			if (!(var_name = get_var_name(&token->content[i])))
			{
				i++;
				continue ;
			}
			substitute_env_var(token, &i, var_name, vars);
			ft_printf("token->content |%s|\n", token->content);
		}
		else if (token->content[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
		{
			escaped = 0;
			i++;
		}
		//TODO check if empty
	}
	return (1);
}
