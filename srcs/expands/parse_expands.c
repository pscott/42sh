#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

static void	print_param_sub_format_error(char *str)
{
	ft_dprintf(2, "%s: %s: bad substitution\n", SHELL_NAME, str);
}

/*
** Functions that expands words in this order:
**		- Tilde
**		- $
**		- Quote removal
*/

t_bool		parse_expands(t_token *token_head, t_vars *vars)
{
	if (!(parse_tildes(token_head, (const char **)vars->env_vars)))//we don't care about this return value
		return (0);
	if (!parse_dollars(token_head, vars)) // check return types ? protect ?
	{
		print_param_sub_format_error(token_head->content);
		return (0);
	}
	parse_quotes(token_head); 	// check return types ? protect ?
	//TODO parse arith_expand here ?? NOP, will be in parse_dollars()
	return (1);
}
