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
	char *str;

	ft_printf("{%s}", token->content);
	if (!ft_strncmp(token->content, "\n", 2))
		str = ft_strdup("newline");
	else
		str = ft_strdup(token->content);
	ft_dprintf(STDERR_FILENO, "42sh: syntax error near unexpected token `%s'", str);
	print_line(2);
	ft_strdel(&str);
}
