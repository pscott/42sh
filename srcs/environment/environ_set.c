#include "ftsh.h"
#include "env.h"

/*
** replace_env_var
** replace an existing env[line] via address "&env[i]"
*/

static void	replace_env_var(char *var_name, char *var_value, char **env_line)
{
	size_t	new_len;
	size_t	var_name_len;

	ft_memdel((void*)&(*env_line));
	new_len = ft_strlen(var_name) + ft_strlen(var_value) + 1;
	if (!(*env_line = ft_strnew(new_len)))
		clean_exit(1, 1);
	ft_strcpy(*env_line, var_name);
	var_name_len = ft_strlen(var_name);
	(*env_line)[var_name_len] = '=';
	if (var_value)
		ft_strcpy(&(*env_line)[var_name_len + 1], var_value);
}

/*
** add_env_var
** realloc env via pointer, with a new line
*/

static void	add_env_var(char *var_name, char *var_value, char ***env)
{
	char	**new_env;
	size_t	env_len;
	int		i;

	env_len = ft_ntab_len((const char **)*env);
	if (!(new_env = (char**)malloc((size_t)sizeof(char**) * (env_len + 2))))
		clean_exit(1, 1);
	i = 0;
	while (*env && (*env)[i])
	{
		if (!(new_env[i] = ft_strdup((*env)[i])))
			clean_exit(1, 1);
		i++;
	}
	if (!(new_env[i] = (char*)malloc(sizeof(char*))))
		clean_exit(1, 1);
	replace_env_var(var_name, var_value, &new_env[i]);
	new_env[i + 1] = NULL;
	ft_free_ntab(*env);
	*env = new_env;
}

/*
** set_env_var
** check if var_name already exist in env
** if so, replace the line with another mallocated on
** else, realloc env to add a new line
*/

void		set_env_var(char *var_name, char *var_value, char ***env)
{
	int		index;

	if ((index = get_envline_index(var_name, *env)) != -1)
	{
		replace_env_var(var_name, var_value, &(*env)[index]);
	}
	else
		add_env_var(var_name, var_value, env);
}
