#include "lexer.h"
#include "ast.h"

/*
**	Returns 0 if token is a pipe (or bigger), or an eat token.
**	Returns 1 on quotes, words, monochars, and redirections.
*/

int			is_argv_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type >= tk_word && probe->type < tk_pipe)
		return (1);
	return (0);
}

/*
**	Returns 0 if token is bigger than a pipe.
**	Else returns 1.
*/

int			is_simple_cmd_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type < tk_pipe)
		return (1);
	else
		return (0);
}
