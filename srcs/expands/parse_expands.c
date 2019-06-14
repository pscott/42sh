#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

/*
**	Returns 0 on success
**	Else returns 1
*/

int			parse_dollars_str(char **str, t_vars *vars)
{
	if (parse_vars(str, vars) > 0)
		return (1);
	if (parse_arith_exp(str, vars) > 0)
		return (1);
	return (0);
}

/*
**	Returns 0 on success
**	Else returns 1
*/

static int	parse_dollars(t_token *token_head, t_vars *vars)
{
	while (token_head && token_head->type < tk_pipe)
	{
		if (token_head->type == tk_word || token_head->type == tk_dq_str)
		{
			if (parse_dollars_str(&token_head->content, vars) > 0)
				return (1);
		}
		token_head = token_head->next;
	}
	return (0);
}

/*
** parse_expands
** return 1 on 'bad substitution' in parse_dollars()
** return 0 otherwise
*/

int			parse_expands(t_token *token_head, t_vars *vars)
{
	parse_tildes(token_head, (const char **)vars->env_vars);
	if (parse_dollars(token_head, vars) > 0)
		return (1);
	parse_quotes(token_head);
	return (0);
}
