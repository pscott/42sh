#include "ftsh.h"
#include "env.h"

/*
**	Copy the env vars into the new env, without the deleted one
*/

static	void	delete_env_index(int todel, char **env, char ***new_env)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	free(env[todel]);
	while (env[i])
	{
		if (i != todel)
			(*new_env)[k++] = env[i];
		i++;
	}
	(*new_env)[k] = NULL;
}

/*
**	Remove a field in an env array
*/

void			unset_env_var(char *var_name, char ***env)
{
	int		env_len;
	int		todel;
	char	**new_env;

	if ((todel = get_envline_index(var_name, *env)) == -1)
		return ;
	env_len = ft_ntab_len((const char **)*env);
	if (!(new_env = (char**)malloc(sizeof(char*) * (env_len - 1 + 1))))
		clean_exit(1, 1);
	delete_env_index(todel, *env, &new_env);
	free(*env);
	*env = new_env;
}
