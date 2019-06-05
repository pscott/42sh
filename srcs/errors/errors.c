#include "ftsh.h"
#include "lexer.h"
#include "line_editing.h"

static int	is_newline_token(t_token *token)
{
	int			i;

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
	ft_dprintf(fd, "42sh: syntax error near unexpected token `%s'\n", str);
	ft_strdel(&str);
}
