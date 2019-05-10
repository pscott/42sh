#include "tosh.h"

//Control operators:
//|| ! && & ; ;; | |& ( )
//	List terminators
//	; &
//	logical operators
//	&& || !
//	pipe operators
//	| |&

t_bool	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

t_bool	is_white_spaces(char c)
{
	//ft_printf("IN WH_SP: {%c}", c);print_line();
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r')//test \r
		return (1);
	return (0);
}

t_bool	is_parenth(char c)
{
	if (c == '[' || c == ']' || c == '(' || c == ')')
		return (1);
	return (0);
}

t_bool	is_metachar(char c)
{
	if (is_white_spaces(c) || is_parenth(c) || is_quotes(c) || c  == '*'
			|| c == '?' || c == '\\' || c == ';' || c == '&'
			|| c == '|' || c == '^' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_bool	is_logic_or_pipe(t_token *token)
{
	if (token->type == TK_OR
			|| token->type == TK_AND || token->type == TK_PIPE)
		return (1);
	return (0);
}

t_bool	is_two_ctrlop_or_redir_following(t_token *prev_token, t_token *current_token)
{
	if (!prev_token)
		return (0);
	if (prev_token->type >= TK_PIPE && current_token->type >= TK_PIPE)
	{
		ft_putstr("333");
		syntax_error_near(current_token);
		ft_memdel((void*)&current_token->content);//test
		ft_memdel((void*)&current_token);//test
		return (1);
	}
	if (is_redir_token(prev_token) && is_redir_token(current_token))
	{
		ft_putstr("444");
		syntax_error_near(current_token);
		return (1);
	}
	return (0);
}

t_bool	is_redir_token(t_token *token)
{
	if (token->type > TK_DQ_STR && token->type <= TK_HEREDOC)
		return (1);
	return (0);
}

t_bool	token_list_start_with_ctrl_op(t_token *prev_token, t_token *current_token)
{
	if (!prev_token && current_token->type >= TK_PIPE)
	{
		ft_putstr("111");
		syntax_error_near(current_token);
		ft_memdel((void*)&current_token->content);
		ft_memdel((void*)&current_token);
		return (1);
	}
	return (0);
}
