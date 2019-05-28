#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

static t_bool	is_param_sub_valid(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i++] && str[i] != '}')
	{
		if (ft_isalnum(str[i]))
			return (0);
	}
}

t_bool	parse_vars(t_token *token, t_vars *vars)
{
	size_t	i;
	char	escaped;

	i = 0;
	escaped = 0;
	//check and replace ${}
	while (token->content[i++])
	{
		if (!escaped && !ft_strncmp("${", &token->content[i], 2))
		{
			if (!(is_param_sub_valid(&token->content[i + 2])))
				return (0);
				//replace
			//
		}
		else if (token->content[i] == '\\')
			escaped = (escaped) ? 0 : 1;
	}
	//replace $
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
		token_head = token_head=>next;
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
	if (!(parse_dollars(token_head, vars)))//if it return 0, stop execution
		return (0);
	parse_quotes(token_head);//i don't think we care about this return value
	return (1);
}
