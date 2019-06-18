#include "lexer.h"
#include "cmd_parsing.h"
#include "env.h"

static char	*get_var_value(t_token **token)
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

//tricky cases:
//	toto='tata'\d"bonsoir"
int		parse_assignation(t_token *token, t_vars *vars)
{
	char	*varline;
	int		ret;

	//(void)vars;
	ret = 0;
	while (token)
	{
		if (token->type == tk_word && ft_strchr(token->content, '='))
		{
			check_for_tilde(&token->content, vars);
			varline = get_var_value(&token);
			//if (token)//debug
			//	ft_printf("AFTER proc |%s|\n", token->content);
			//add varline to an assignation table ??
			add_varline(varline, &vars->assign_tab);
			ft_strdel(&varline);
			ret = 1;
		}
		else if (token->type != tk_eat)
			break;
		if (token)
			token = token->next;
	}
	return (ret);
}

///void	apply_assignation(char **assign_tab, char ***vars_tab)
///{
///	int		i;
///	t_vars	*vars;//i should not use the global
///
///	vars = get_vars(NULL);
///	ft_dprintf(2, "in apply_ass\n");
///	if (!assign_tab || !assign_tab[0])
///		return ;
///	i = 0;
///	while (assign_tab[i])
///	{
///		add_varline(assign_tab[i], vars_tab);
///		i++;
///	}
///}

void	apply_assignation_to_ntab(char **assign_tab, char ***ntab)
{
	int		i;

	if (!assign_tab || !assign_tab[0])
		return ;
	i = -1;
	while (assign_tab[++i])
		add_varline(assign_tab[i], ntab);
}
void	apply_assignation(char **assign_tab, t_vars *vars)
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
		{
			add_varline(assign_tab[i], &vars->env_vars);
		}
		ft_strdel(&var_name);
	}
}
