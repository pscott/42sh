#include "tosh.h"

/*
void	error_mem(char *func_name)
{
	ft_putstr_fd("malloc failed in ", 2);
	ft_putstr_fd(func_name, 2);
	ft_putendl_fd(".", 2);
	clean_exit(EXIT_FAILURE);
}
*/

void	error_mem(void)
{
	ft_putendl_fd("memory error.", STDERR_FILENO);
	clean_exit(EXIT_FAILURE);
}

void	syntax_error_near(t_token *token)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (ft_strcmp(token->content, "\n") == 0)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token->content, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
