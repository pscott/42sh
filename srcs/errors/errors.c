#include "ftsh.h"
#include "lexer.h"
#include "line_editing.h"
#include "errors.h"

static int		is_newline_token(t_token *token)
{
	int			i;

	if (!token || !token->content)
		return (1);
	i = -1;
	while (token->content[++i])
	{
		if (token->content[i] == '\n')
			return (1);
	}
	return (0);
}

void			syntax_error_near(t_token *token)
{
	char		*str;
	int			fd;

	fd = STDERR_FILENO;
	if (is_newline_token(token))
		str = ft_strdup("newline");
	else
		str = ft_strdup(token->content);
	if (!str)
		clean_exit(1, 1);
	ft_dprintf(fd, SHELL_NAME ": syntax error near unexpected token `%s'\n",
		str);
	ft_strdel(&str);
}
