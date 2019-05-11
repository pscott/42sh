#include "lexer.h"
#include "ast.h"

/*
** Functions that expands words in this order:
**		- Tilde
**		- $
**		- Quote removal
*/

t_bool		parse_expands(t_token *token_head, char **env)
{
	if (!(parse_tildes(token_head, (const char **)env)))
		return (0);
	parse_dollars(token_head, env); // check return types ? protect ?
	parse_quotes(token_head); 	// check return types ? protect ?
	return (1);
}
