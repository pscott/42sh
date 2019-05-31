//#include "42sh.h"
//#include "lexer.h"
#include "cmd_parsing.h"

//*i is index[0]
static void			substitute_param(t_token *token, size_t *i, const char *var_name
		, t_vars *vars)
{
	const char	*var_value;
	size_t		index[2];
	
	if (!(var_value = get_envline_value((char *)var_name, vars->env_vars)))
		var_value = &var_name[ft_strlen(var_name)];//toujours aussi degueu
	index[0] = *i;
	// aa${PWD}aa
	//   ^2    ^8
	index[1] = *i + ft_strlen(var_name) + 4;
	ft_printf("var_value: |%s| len:%ld\n", var_value, ft_strlen(var_value));
	*i += ft_strlen(var_value) - 1;//test -1
	substitute_slice(&token->content, index, var_value);
	ft_strdel((char**)&var_name);
}

static const char	*get_param_sub_name(const char *str)
{
	size_t	i;

	i = 2;
	while (str[i++] && str[i] != '}')
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


t_bool				parse_param_sub(t_token *token, t_vars *vars)
{
	size_t		i;
	t_bool		escaped;
	const char	*var_name;

	i = 0;
	escaped = 0;
	ft_printf("------------------|%s|\n", token->content);
	while (token->content[i])
	{
		ft_printf("parse_param_sub i: %ld\n", i);
		if (!escaped && !ft_strncmp("${", token->content + i, 2)
				&& is_terminated("${", "}", token->content + i))
		{
			if (!(var_name = get_param_sub_name(token->content + i)))//this print 'bad sub'
			{
				ft_printf("get_param_sub_name failed\n");//debug
				return (0);
			}
			ft_printf("var_name: |%s|\n", var_name);
			substitute_param(token, &i, var_name, vars);
			ft_printf("$$ content: |%s| i: %ld\n", token->content, i);
		}
		else if (token->content[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
		{
			escaped = 0;
			i++;
		}
	}
	//TODO check if empty
	return (1);
}
