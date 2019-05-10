#include "lexer.h"
#include "ast.h"

t_bool	is_quote_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TK_DQ_STR || token->type == TK_SQ_STR)
		return (1);
	return (0);
}

t_bool		is_argv_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type > TK_EAT && probe->type < TK_PIPE)
		return (1);
	return (0);
}

t_bool	is_simple_cmd_token(t_token *probe) //static ?
{
	if (!probe)
		return (0);
	if (probe->type < TK_PIPE)
		return (1);
	else
		return (0);
}
