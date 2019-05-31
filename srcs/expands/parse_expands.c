#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

//loop through token list
//parse for $ and ${}, return 0 on bad substitution (and stop exec)
static t_bool	parse_dollars(t_token *token_head, t_vars *vars)
{
	while (token_head && token_head->type < tk_pipe)
	{
		if (token_head->type == tk_word || token_head->type == tk_dq_str)
		{
			if (!(parse_param_sub(&token_head->content, vars)))
			{
				ft_printf("parse_param_sub() return (0)\n");
				return (0);
			}
			if (!(parse_env_var(&token_head->content, vars)))//protection needed ?
			{
				ft_printf("parse_env_var() return (0)\n");
				return (0);
			}
			//then reparse for $((, return 0 on 'unexpected char'
			if (!(parse_arith_exp(&token_head->content, vars)))
			{
				ft_printf("parse_arith_exp() returned 0\n");
				return (0);
			}
			//don't make tk_eat
			//if (!(ft_strlen(token_head->content)))
			//	token_head->type = tk_eat;
		}
		token_head = token_head->next;
	}
	return (1);
}

/*
** parse_expands
** return 0 on 'bad substitution' in parse_dollars()
** return 1 otherwise
*/

t_bool			parse_expands(t_token *token_head, t_vars *vars)
{
	parse_tildes(token_head, (const char **)vars->env_vars);//we don't care about return value
	if (!(parse_dollars(token_head, vars)))//if it return 0, TODO stop execution
		return (0);
	parse_quotes(token_head);//i don't think we care about this return value
	return (1);
}
