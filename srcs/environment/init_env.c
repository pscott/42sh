#include "tosh.h"

static void	bzero_env(char **env, int size)
{
	while (size >= 0)
		env[size--] = NULL;
}

/*
** create_minienv
** malloc a minienv
** set SHLVL=1 and PWD
** and return it
*/

static char	**create_minienv(void)
{
	int		init_lines;
	char	**env;
	char	*cwd;

	init_lines = 2;
	if (!(env = (char**)malloc(sizeof(char**) * (init_lines + 1))))
		ERROR_MEM;
	bzero_env(env, init_lines);
	set_env_var("SHLVL", "1", &env);
	if (!(cwd = getcwd(NULL, 0)))//getcwd can fail in other way than ERROR_MEM
		ERROR_MEM;
	set_env_var("SHLVL", "1", &env);
	set_env_var("PWD", cwd, &env);
	env[init_lines - 0] = NULL;
	ft_memdel((void*)&cwd);
	return (env);
}

/*
** init_env
** return a copy of env if it exist and set_shlvl
** return a fresh minienv otherwise
*/

char		**init_env(const char **env)
{
	char	**new_env;

	if (env && *env)
	{
		if (!(new_env = ft_dup_ntab(env)))
			return (NULL);//ERROR_MEM;
		set_shlvl(&new_env);
		return (new_env);
	}
	else
		return (create_minienv());
}
