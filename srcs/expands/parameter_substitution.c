#include "42sh.h"
#include "lexer.h"

//static t_bool	is_tk_param_sub_well_formated(t_token *token)
//{
//	size_t	i;
//
//	if (token->content[2] == '}')
//		return (0);
//	i = 0;
//	while (token->content[i++] && token->content[i] != '}')
//		if (!ft_isalnum(token->content[i]) && token->content[i] != '_')
//			return (0);
//	return (1);
//}
