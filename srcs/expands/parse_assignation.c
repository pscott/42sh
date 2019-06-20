#include "lexer.h"
#include "cmd_parsing.h"
#include "env.h"

/*
** get_concatenate_varline
** concat all token of the assignation to get a 'varline'
*/

static char	*get_concatenate_varline(t_token **token)
{
	char	*res_str;

	res_str = NULL;
	while (*token && (*token)->type >= tk_word && (*token)->type <= tk_dq_str)
	{
		res_str = ft_strjoin_free_left(res_str, (*token)->content);
		(*token)->type = tk_eat;
		*token = (*token)->next;
	}
	return (res_str);
}

/*
** check_for_tilde
** replace the tilde if it's the first char of the var_value
*/

static void	check_for_tilde(char **str, t_vars *vars)
{
	int		i;
	size_t	index[2];
	char	*home_str;

	i = 0;
	while ((*str)[i] && (*str)[i] != '=')
		i++;
	if ((*str)[i] == '=' && (*str)[i + 1] == '~')
	{
		index[0] = i + 1;
		index[1] = i + 1;
		if (!(home_str = get_varline_value("HOME", vars->env_vars)))
		{
			if (vars->verbose)
				ft_dprintf(2, "error: HOME not set\n");
			return ;
		}
		substitute_slice(str, index, home_str);
		ft_strdel(&home_str);
	}
}

/*
** parse_assignation
** is the main function of assignation
** It parse the token list looking for assignation
** concatenate all assignation token to get a 'varline'
** add it to assign_tab
**
** return 0 if no assignation is found
*/

int			parse_assignation(t_token *token, t_vars *vars)
{
	char	*varline;
	int		ret;

	ret = 0;
	while (token)
	{
		if (token->type == tk_word && ft_strchr(token->content, '=')
			&& is_valid_varname(token->content))
		{
			check_for_tilde(&token->content, vars);
			varline = get_concatenate_varline(&token);
			add_varline(varline, &vars->assign_tab);
			ft_strdel(&varline);
			ret = 1;
		}
		else if (token->type != tk_eat)
			break ;
		if (token)
			token = token->next;
	}
	return (ret);
}

/*
**	apply_assignation_to_ntab
**	apply all assign_tab to the given ntab
*/

void		apply_assignation_to_ntab(char **assign_tab, char ***ntab)
{
	int		i;

	if (!assign_tab || !assign_tab[0])
		return ;
	i = -1;
	while (assign_tab[++i])
		add_varline(assign_tab[i], ntab);
}

/*
** apply_assignation
** apply already parsed assignation to vars->shell_vars
** If one of the variables is found in env: apply to env too
*/

void		apply_assignation(char **assign_tab, t_vars *vars)
{
	int		i;
	char	*var_name;

	if (!assign_tab || !assign_tab[0])
		return ;
	i = -1;
	while (assign_tab[++i])
	{
		add_varline(assign_tab[i], &vars->shell_vars);
		if (!(var_name = get_name_from_varline(assign_tab[i])))
			continue ;
		if (get_envline(var_name, vars->env_vars))
			add_varline(assign_tab[i], &vars->env_vars);
		ft_strdel(&var_name);
	}
}
