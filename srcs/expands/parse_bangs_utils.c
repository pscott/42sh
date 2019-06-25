#include "lexer.h"
#include "ast.h"
#include "line_editing.h"
#include "cmd_parsing.h"
#include "history.h"
#include "errors.h"

void			refresh_i(int nb, int *i, int ret)
{
	if (ret == 2)
		++(*i);
	while ((nb = nb / 10))
		++(*i);
}

int				is_quoted_char(char *s, int i, char c)
{
	if (s[i] == c)
	{
		if (i > 0)
		{
			if (s[i - 1] == '\\')
				return (1);
		}
	}
	return (0);
}

int				go_to_matching_sqt(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i])
	{
		if ((*str)[*i] == '\'' && !is_quoted_char(*str, *i, '\''))
			break ;
		else
			++(*i);
	}
	return (0);
}

int				go_to_matching_dqt(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i])
	{
		if ((*str)[*i] == '\"' && !is_quoted_char(*str, *i, '\"'))
			break ;
		else
			++(*i);
	}
	return (0);
}
