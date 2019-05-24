#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

/*
** Functions that expands words in this order:
**		- Tilde
**		- $
**		- Quote removal
*/

t_bool		parse_expands(t_token *token_head, t_vars *vars)
{
	if (!(parse_tildes(token_head, (const char **)vars->env_vars)))
		return (0);
	parse_dollars(token_head, vars); // check return types ? protect ?
	parse_quotes(token_head); 	// check return types ? protect ?
	//TODO parse arith_expand here ?? or in_parse_dollars ?
	return (1);
}
