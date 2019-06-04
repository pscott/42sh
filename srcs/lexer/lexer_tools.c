#include "ftsh.h"
#include "errors.h"

/*
**	Control operators:
**	|| ! && & ; ;; | |& ( )
**	List terminators:
**	; &
**	logical operators:
**	&& || !
**	pipe operators:
**	| |&
*/

int		is_logic_or_pipe(t_token *token)
{
	if (token->type == tk_or
		|| token->type == tk_and || token->type == tk_pipe)
		return (1);
	return (0);
}

int		is_two_ctrlop_or_redir_following(t_token *prev_token, t_token *current_token)
{
	if (!prev_token)
		return (0);
	if (prev_token->type >= tk_pipe && current_token->type >= tk_pipe)
	{
		syntax_error_near(current_token);
		ft_memdel((void*)&current_token->content);
		ft_memdel((void*)&current_token);
		return (1);
	}
	if (is_redir_token(prev_token) && is_redir_token(current_token))
	{
		syntax_error_near(current_token);
		return (1);
	}
	return (0);
}

int		is_redir_token(t_token *token)
{
	if (token->type > tk_dq_str && token->type <= tk_heredoc)
		return (1);
	return (0);
}

int		token_list_start_with_ctrl_op(t_token *prev_token, t_token *current_token)
{
	if (!prev_token && current_token->type >= tk_pipe)
	{
		syntax_error_near(current_token);
		ft_memdel((void*)&current_token->content);
		ft_memdel((void*)&current_token);
		return (1);
	}
	return (0);
}
