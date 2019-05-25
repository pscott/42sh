#include "expand.h"

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

char		*get_var_name(char *str)
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
** substitute_env_var
** realloc and return a new string with expanded variable
** set the index 'i' accordingly
** free (old_str && var_name)
*/

char		*substitute_env_var(char *old_str, size_t *i
		, char *var_value, char *var_name)
{
	char	*new_str;

	if (!(new_str = ft_strnew(ft_strlen(old_str)
		- (ft_strlen(var_name) + 1) + ft_strlen(var_value))))
		ERROR_MEM;
	ft_strncpy(new_str, old_str, *i);
	ft_strcpy(new_str + *i, var_value);
	*i += ft_strlen(var_value);
	ft_strcpy(new_str + *i,
		old_str + *i - ft_strlen(var_value) + (ft_strlen(var_name) + 1));
	(*i)--;
	ft_memdel((void*)&old_str);
	ft_memdel((void*)&var_name);
	return (new_str);
}

/*
** expand_dollars
** parse token->content until an unescaped '$' is found,
** then try to replace the env_var:
** - if the env_var doesn't exist, replace with nothing
** - if the env_var does exist, substitute by it value
**
** if the token->content is empty after this, token->type = TK_EAT
*/

static t_bool	expand_dollars(t_token *token, t_vars *vars)//TODO expand ARITH here ??
{
	size_t	i;
	char 	*var_name;
	char	*var_value;

	i = 0;
	while (token->content[i])
	{
		if ((token->content[0] == '$') || (i > 0 && token->content[i] == '$'
			&& token->content[i - 1] != '\\'))
		{
			if (!(var_name = get_var_name(token->content + i)))
			{
				i++;
				continue ;
			}
			if (!(var_value = get_envline_value(var_name, vars->env_vars)))
				var_value = &var_name[ft_strlen(var_name)];
			token->content = substitute_env_var(token->content, &i,
				var_value, var_name);
		}
		i++;
	}
	if (ft_strlen(token->content) == 0)
		token->type = tk_eat;
	return (0);
}

//check return type
//TODO need arith_expand in tk_dq_str
t_bool			parse_dollars(t_token *token_head, t_vars *vars)
{
	t_bool		res;
	long long	arith_res;
	char		*tmp_str;

	res = 0;
	arith_res = 0;
	while (token_head && token_head->type < tk_pipe)
	{
		if (token_head->type == tk_word || token_head->type == tk_dq_str)
		{
			res = 1;
			expand_dollars(token_head, vars);
		}
		else if (token_head->type == tk_arith_exp)//test
		{
			//tmp_str = ft_strndup(&token_head->content[3], ft_strlen(token_head->content) - 5);
			tmp_str = ft_strdup(token_head->content);
			ft_printf("duped={%s}\n", tmp_str);
			expansion_arith(tmp_str, &vars->env_vars, &arith_res);
			ft_printf("result = {%lld}\n", arith_res);
			token_head->content = ft_itoa(arith_res);
			token_head->type = tk_word;//pas sure: "cat not_exist $((2))>&-"
			ft_printf("token: {%s}\n", token_head->content);
			//token_head->content = ft_itoa(expansion_arith(tmp_str, &vars->env_vars, &arith_res));
			//ft_printf("ARITH_RES = {%lld}\n", token_head->content);
		}
		token_head = token_head->next;
	}
	return (res);
}
