#include "lexer.h"
#include "ast.h"

/*
** Functions that expans words in this order:
**		- Tilde
**		- $
**		- Quote removal
**	Then calls parse_redir to look for redirections
*/

t_bool		parse_expands(t_token *token_head, int in, int out, char **env)
{
	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	if (!(parse_tildes(token_head, (const char **)env)))
		return (0);
	parse_dollars(token_head, env);
	parse_quotes(token_head);
	return (parse_redirections(token_head));
}
