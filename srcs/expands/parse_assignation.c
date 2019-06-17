#include "lexer.h"
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
	ft_dprintf(2, "RES_STR: %s\n", res_str);
	return (res_str);
}

//tricky cases:
//	toto='tata'\d"bonsoir"
void	parse_assignation(t_token *token, t_vars *vars)
{
	char		*varline;

	(void)vars;
	dprintf(2, "==parse_ass==tk_list==\n");
	print_token_list(token);
	dprintf(2, "======================\n");
	while (token)
	{
		if (token->type == tk_word && ft_strchr(token->content, '='))
		{
			ft_printf("procs on |%s|\n", token->content);
			varline = get_var_value(&token);
			if (token)//debug
				ft_printf("AFTER proc |%s|\n", token->content);
			//add varline to an assignation table ??
			add_varline(varline, &vars->assign_tab);
		}
		else if (token->type != tk_eat)
			break;
		if (token)
			token = token->next;
	}
}

void	apply_assignation(char **assign_tab, char ***vars_tab)
{
	int		i;

	ft_dprintf(2, "in apply_ass\n");
	if (!assign_tab || !assign_tab[0])
		return ;
	i = 0;
	while (assign_tab[i])
	{
		add_varline(assign_tab[i], vars_tab);
		i++;
	}
}
