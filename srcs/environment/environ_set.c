#include "ftsh.h"
#include "env.h"
#include "hashmap.h"

/*
** replace_env_var
** replace an existing env[line] via address "&env[i]"
*/

static void	replace_env_var(char *var_name, char *var_value, char **env_line)
{
	size_t	new_len;
	t_vars	*vars;
	size_t	var_name_len;

	if (!env_line)
		return ;
	ft_memdel((void*)env_line);
	var_name_len = ft_strlen(var_name);
	new_len = var_name_len + ft_strlen(var_value) + 1;
	if (!(*env_line = ft_strnew(new_len)))
		clean_exit(1, 1);
	ft_strcpy(*env_line, var_name);
	if (*env_line)
		(*env_line)[var_name_len] = '=';
	if (var_value)
		ft_strcpy(&(*env_line)[var_name_len + 1], var_value);
	if (ft_strncmp(var_name, "PATH", 5) == 0)
	{
		vars = get_vars(NULL);
		reset_hashmap(&vars->hashmap);
	}
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
	if (!(new_env = (char**)malloc(sizeof(char*) * (env_len + 2))))
		clean_exit(1, 1);
	i = 0;
	while (*env && (*env)[i])
	{
		if (!(new_env[i] = ft_strdup((*env)[i])))
			clean_exit(1, 1);
		i++;
	}
	new_env[i] = NULL;
	replace_env_var(var_name, var_value, &(new_env[i]));
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
		replace_env_var(var_name, var_value, &(*env)[index]);
	else
		add_env_var(var_name, var_value, env);
}
