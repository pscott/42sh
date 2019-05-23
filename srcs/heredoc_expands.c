#include "heredoc.h"

/*
** heredoc_expand_dollars
*/

t_bool	heredoc_expand_dollars(char **txt, t_vars *vars)
{
	size_t	i;
	char 	*var_name;
	char	*var_value;

	i = 0;
	while ((*txt)[i])
	{
		if (((*txt)[0] == '$') || (i > 0 && (*txt)[i] == '$'
			&& (*txt)[i - 1] != '\\'))
		{
			if (!(var_name = get_var_name(*txt + i)))
			{
				i++;
				continue ;
			}
			if (!(var_value = get_envline_value(var_name, vars->env_vars)))
				var_value = &var_name[ft_strlen(var_name)];
			//for later free
			*txt = ft_strdup(*txt);
			//
			*txt = substitute_env_var(*txt, &i,
				var_value, var_name);
		}
		i++;
	}
	//if (ft_strlen(token->content) == 0)
	//	token->type = tk_eat;
	return (0);
}
