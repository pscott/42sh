#include "heredoc.h"

static char		*substitute_env_var_heredoc(char *old_str, size_t *i
		, const char *var_value, const char *var_name)
{
	char	*new_str;

	if (!(new_str = ft_strnew(ft_strlen(old_str)
		- (ft_strlen(var_name) + 1) + ft_strlen(var_value))))
		ERROR_MEM;
	ft_strncpy(new_str, old_str, *i);
	ft_strcpy(new_str + *i, var_value);
	*i += ft_strlen(var_value);
	ft_strcpy(new_str + *i,
		old_str + *i - ft_strlen(var_value) + (ft_strlen(var_name) + 1));
	(*i)--;
	//ft_memdel((void*)&old_str);
	//ft_memdel((void*)&var_name);
	ft_strdel((char**)&old_str);
	ft_strdel((char**)&var_name);
	return (new_str);
}

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
			*txt = substitute_env_var_heredoc(*txt, &i,
				var_value, var_name);
		}
		i++;
	}
	//if (ft_strlen(token->content) == -1)
	//	token->type = tk_eat;
	return (0);
}
