#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

void	substitute_param(t_token *token, size_t *i, const char *var_name
		, t_vars *vars)
{
	const char	*var_value;
	size_t		new_size;
	char		*new_str;

	if (!(var_value = get_envline_value(var_name, vars->env_vars)))
		var_value = &var_name[ft_strlen(var_name)];//toujours aussi degueu
	new_size = ft_strlen(token->content) - 3 - ft_strlen(var_name) + ft_strlen(var_value);
	if (!(new_str = ft_strnew(new_size)))
		ERROR_MEM;
	ft_strncpy(new_str, token->content, *i);
	ft_strcpy(new_str + *i, var_value);
	*i += ft_strlen(var_value);
	ft_strcpy(new_str + *i, token->content + *i - ft_strlen(var_value) + ft_strlen(var_name) + 3);//check '+ 3'
	ft_strdel(&token->content);
	token->content = new_str;
	ft_strdel(&var_name);
}

//static t_bool	is_param_sub_valid(const char *str)
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
	{
		ft_printf("TMP: get_param_sub_name WORKED !\n");
		return (ft_strndup(&str[2], i - 3));
	}
	return (NULL);
}

t_bool	parse_vars(t_token *token, t_vars *vars)
{
	size_t		i;
	char		escaped;
	const char	*var_name;
	const char	*var_value;

	i = 0;
	escaped = 0;
	//check and replace ${}
	while (token->content[i++])
	{
		if (!escaped && !ft_strncmp("${", &token->content[i], 2))
		{
			if (!(var_name = get_param_sub_name(&token->content[i])))
				return (0);
			substitute_param(token, &i, var_name, vars);
			//check (*i value) plz
		}
		else if (!escaped && token->content[i] == '$')
		{
			if (!(var_name = get_var_name(&token->content[i])))
				continue ;//check me
			if (!(var_value = get_envline_value(var_name, vars->env_vars)))
				var_value = &var_name[ft_strlen(var_name)];
			token->content = substitute_env_var(token->content, &i,
				var_value, var_name);
		}
		else if (token->content[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else//test: pas sure
			escpaped = 0;
	}
	if (ft_strlen(token->content) == 0)
		token->type = tk_eat;
	return (1);
}

t_bool	parse_arith_exp(t_token *token, t_vars *vars)
{
	size_t	i;
	char	escaped;

	i = 0;
	escaped = 0;
	while (token->content[i++])
	{
		if (!escaped && !ft_strncmp("$((", &token->content[i], 3))
		{
			//get matching '))'
			//	else print like this
			//if arith_exp
			//	replace with itoa?
			//	and move (i)
			//else
			//	return (0);//error: bad sub ?
		}
		else if (token->content[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else//test: pas sure
			escpaped = 0;
	}//no need to check if empty for arith_exp
}

//loop through token list
t_bool	parse_dollars(t_token *token_head, t_vars *vars)
{
	while (token_head && token_head->type < tk_pipe)
	{
		//parse for $ and ${}, return 0 on bad substitution (and stop exec)
		if (!(parse_vars(token_head, vars)))
			return (0);
		//then reparse for $((, return 0 on 'unexpected char'
		if (!(parse_arith_exp(token_head, vars)))
			return (0);
		token_head = token_head->next;
	}
	return (1);
}

/*
** parse_expands
** return 0 on bad substitution in parse dollars
** return 1 otherwise
*/

t_bool	parse_expands(t_token *token_head, t_vars *vars)
{
	parse_tildes(token_head, (const char **)vars->env_vars);//we don't care about return value
	if (!(parse_dollars(token_head, vars)))//if it return 0, TODO stop execution
		return (0);
	parse_quotes(token_head);//i don't think we care about this return value
	return (1);
}
