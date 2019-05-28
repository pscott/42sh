#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

static void	print_param_sub_format_error(char *str)
{
	ft_dprintf(2, "%s: %s: bad substitution\n", SHELL_NAME, str);
}

static t_bool	check_bad_substitution(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '}')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: bad substitution\n"
				, SHELL_NAME, str);
			return (0);
		}
	}
	return (1);
}

static t_bool	is_param_expand_correct(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] == 0)
		return (0);//check me
	if (str[i] == '}')
		return (check_bad_substitution(str));
}

static t_bool	expand_variables(t_token *token, t_vars *vars)
{
	size_t	i;
	char	escaped;

	i = 0;
	escaped = 0;
	while (token->content[i++])
	{
		if (!escaped && !ft_strncmp("${", &token->content[i], 2))
		{
			//do not use 'is_matched' for this case
			//${ can be unclosed if it is in dquot
			if (is_param_expand_correct(token->content) == 0)

		}
	}
}

static t_bool	parse_variables(t_token *token_head, t_vars *vars)
{
	while (token_head && token_head->type < tk_pipe)
	{
		if (token_head->type == tk_word || token_head->type == tk_dq_str)
		{
			expand_variables(token_head, vars);
		}
	}
}

/*
** Functions that expands words in this order:
**		- Tilde
**		- $ and ${}
**		- $(())
**		- Quote removal
*/

t_bool		parse_expands(t_token *token_head, t_vars *vars)
{
	if (!(parse_tildes(token_head, (const char **)vars->env_vars)))//we don't care about this return value
		return (0);
	//parse_variables(token_head, vars)
	parse_variables(token_head, vars);
	//parse_arithmetique(token_head, vars)
	if (!parse_dollars(token_head, vars)) // check return types ? protect ?
	{
		print_param_sub_format_error(token_head->content);
		return (0);
	}
	parse_quotes(token_head); 	// check return types ? protect ?
	//TODO parse arith_expand here ?? NOP, will be in parse_dollars()
	return (1);
}
