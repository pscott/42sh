#include "42sh.h"
#include "lexer.h"
#include "line_editing.h"

void	error_mem(void) //unused but should use ?
{
	ft_putendl_fd("memory error.", STDERR_FILENO);
	clean_exit(EXIT_FAILURE);
}

void	syntax_error_near(t_token *token)
{
	ft_putstr_fd(STD_PROMPT, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (ft_strcmp(token->content, "\n") == 0)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token->content, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
