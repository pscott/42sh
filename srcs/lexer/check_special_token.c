#include "ftsh.h"
#include "errors.h"
#include "lexer.h"
#include "input.h"

static void		modif_ints(unsigned int *braces_count, int braces_to_add,
				int *i, int i_to_add)
{
	*braces_count += braces_to_add;
	*i += i_to_add;
}

static t_token	*last_check_arith_exp(char **cmdline, int i,
				unsigned int braces_count)
{
	t_token	*token;

	if (braces_count == 0 && (token = create_token(*cmdline, i, tk_word)))
		*cmdline = *cmdline + i;
	else
		return (NULL);
	return (token);
}

t_token			*check_arith_exp_token(char **cmdline)
{
	unsigned int	braces_count;
	int				i;
	int				escaped;

	braces_count = 0;
	escaped = 0;
	i = -1;
	while ((*cmdline)[++i])
	{
		if (!escaped && (*cmdline)[i] == '\\' && (*cmdline)[i + 1] == '\n')
			return (trim_escaped_newline());
		if (!ft_strncmp("$((", (*cmdline) + i, 3))
			modif_ints(&braces_count, 1, &i, 2);
		else if (!ft_strncmp("))", (*cmdline) + i, 2))
		{
			modif_ints(&braces_count, -1, &i, 1);
			if (braces_count == 0 && ++i)
				break ;
		}
		else
			escaped = adjust_escaped((*cmdline)[i], escaped);
	}
	return (last_check_arith_exp(cmdline, i, braces_count));
}

t_token			*check_param_sub_token(char **cmdline)
{
	t_token	*token;
	size_t	i;
	int		escaped;

	i = 0;
	escaped = 0;
	while ((*cmdline)[i] && (*cmdline)[i] != '}')
	{
		if (!escaped && (*cmdline)[i] == '\\' && (*cmdline)[i + 1] == '\n')
			return (trim_escaped_newline());
		else
			escaped = adjust_escaped((*cmdline)[i], escaped);
		i++;
	}
	if ((*cmdline)[i] == 0)
		return (NULL);
	i++;
	if (!(token = create_token(*cmdline, i, tk_word)))
		clean_exit(1, MALLOC_ERR);
	*cmdline = *cmdline + i;
	return (token);
}

int				is_ctrl_op_following_a_redir_token(t_token *prev,
	t_token *curr)
{
	if (is_redir_token(prev) && curr->type >= tk_pipe)
	{
		syntax_error_near(curr);
		free_token_list(curr);
		return (1);
	}
	return (0);
}
