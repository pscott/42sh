#include "ftsh.h"
#include "env.h"
#include "errors.h"

static void	bzero_env(char **env, size_t size)
{
	size_t i;

	i = 0;
	if (!env)
		return ;
	while (i <= size)
		env[i++] = NULL;
}

/*
** create_minienv
** malloc a minienv
** set SHLVL=1 and PWD
** and return it
*/

static char	**create_minienv(void)
{
	size_t	init_lines;
	char	**env;
	char	*cwd;

	ft_dprintf(2, "IN create_minienv\n");
	init_lines = 2;
	if (!(env = (char**)malloc(sizeof(char*) * (init_lines + 1))))
		clean_exit(1, 1);
	bzero_env(env, init_lines);
	set_env_var("SHLVL", "1", &env);
	if (!(cwd = getcwd(NULL, 0)))
		print_errors(ERR_GETCWD, ERR_GETCWD_STR, NULL);
	set_env_var("SHLVL", "1", &env);
	if (cwd)
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
			clean_exit(1, 1);
		set_shlvl(&new_env);
		return (new_env);
	}
	else
		return (create_minienv());
}
