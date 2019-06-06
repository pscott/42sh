#include "ftsh.h"
#include "lexer.h"
#include "input.h"

static t_token	*get_dquot_token(char **cmdline)
{
	t_token		*token;
	size_t		i;
	int			escaped;

	i = 1;
	escaped = 0;
	while ((*cmdline)[i] != 0)
	{
		if (!escaped && (*cmdline)[i] == '"')
			break ;
		if (!escaped && (*cmdline)[i] == '\\' && (*cmdline)[i + 1] == '\n')
			return (trim_escaped_newline());
		else if ((*cmdline)[i] == '\\')
			escaped = (escaped) ? 0 : 1;
		else
			escaped = 0;
		i++;
	}
	if ((*cmdline)[i] == 0)
		return (NULL);
	if (!(token = create_token(*cmdline, ++i, tk_dq_str)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_squot_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((*cmdline)[i] && (*cmdline)[i] != '\'')
		i++;
	if ((*cmdline)[i] == 0)
		return (NULL);
	if (!(token = create_token(*cmdline, ++i, tk_sq_str)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_regular_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while ((*cmdline)[i] && !ft_is_metachar((*cmdline)[i]))
	{
		if ((*cmdline)[i] == '$' && i != 0)
			break ;
		i++;
	}
	if (!(token = create_token(*cmdline, i, tk_word)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_monochar(char **cmdline)
{
	t_token			*token;

	if (*(*cmdline + 1) == '\n')
		return (trim_escaped_newline());
	(*cmdline)++;
	if (!(**cmdline))
		return (NULL);
	token = create_token(*cmdline, 1, tk_monoc);
	(*cmdline)++;
	return (token);
}

/*
** get_token
** return a malloced token accordingly to the character under the cmdline
** pointer
** all sub get_token functions move the cmdline pointer accordingly
** and return NULL when they fail to get the token, so lexer send LEX_CONT_READ
** to handle_input
*/

t_token			*get_token(char **cmdline, t_operation *op_chart)
{
	t_token	*token;

	if (**cmdline == '"')
		return (get_dquot_token(cmdline));
	else if (**cmdline == '\'')
		return (get_squot_token(cmdline));
	else if (**cmdline == '\\')
		return (get_monochar(cmdline));
	else if (ft_is_white_space(**cmdline))
		return (get_eat_token(cmdline));
	else if ((ft_strnlen(*cmdline, 3) == 3) && !ft_strncmp(*cmdline, "$((", 3))
		return (check_arith_exp_token(cmdline));
	else if ((ft_strnlen(*cmdline, 2) == 2) && !ft_strncmp(*cmdline, "${", 2))
		return (check_param_sub_token(cmdline));
	else if ((token = get_op_chart_token(cmdline, op_chart)))
		return (token);
	else
		return (get_regular_token(cmdline));
}
