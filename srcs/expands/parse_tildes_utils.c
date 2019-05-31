#include "lexer.h"
#include "ast.h"

t_bool	is_valid_tilde(const char *str, t_token *prev_token)
{
	if (!prev_token && (!ft_strncmp("~/", str, 2) || !ft_strncmp("~", str, 2)))
		return (1);
	if (prev_token && prev_token->type == tk_eat
		&& (!ft_strncmp("~/", str, 2) || !ft_strncmp("~", str, 2)))
		return (1);
	if (!prev_token && (!ft_strncmp("~", str, 1)))
		return (2);
	if (prev_token && prev_token->type == tk_eat
		&& (!ft_strncmp("~", str, 1)))
		return (2);
	return (0);
}
