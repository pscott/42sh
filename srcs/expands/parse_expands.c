#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

//parse_param_sub and parse_env_var should be done at the same time
//echo $SHLVL${SHLVL}
t_bool			parse_dollars_str(char **str, t_vars *vars)
{
	ft_printf("STEP1|%s\n", *str);
	if (!(parse_param_sub(str, vars)))
	{
		ft_printf("parse_param_sub() return (0)\n");
		return (0);
	}
	ft_printf("STEP2|%s\n", *str);
	//if (!(parse_env_var(str, vars)))//protection needed ?
	//{
	//	ft_printf("parse_env_var() return (0)\n");
	//	return (0);
	//}
	//ft_printf("STEP3|%s\n", *str);
	//then reparse for $((, return 0 on 'unexpected char'
	if (!(parse_arith_exp(str, vars)))
	{
		ft_printf("parse_arith_exp() returned 0\n");
		return (0);
	}
	ft_printf("STEP4|%s\n", *str);
	//don't make tk_eat
	//if (!(ft_strlen(token_head->content)))
	//	token_head->type = tk_eat;
	return (1);
}

//loop through token list
//parse for $ and ${}, return 0 on bad substitution (and stop exec)
static t_bool	parse_dollars(t_token *token_head, t_vars *vars)
{
	while (token_head && token_head->type < tk_pipe)
	{
		if (token_head->type == tk_word || token_head->type == tk_dq_str)
		{
			if (parse_dollars_str(&token_head->content, vars) == 0)
				return (0);
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
