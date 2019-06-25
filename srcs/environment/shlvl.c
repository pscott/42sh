#include "ftsh.h"
#include "env.h"

/*
** set_shlvl
** set the SHLVL of the given env via adress
*/

void	set_shlvl(char ***env)
{
	char	*value;
	int		shlvl;
	char	*tmp;

	if ((value = get_envline_value("SHLVL", *env)))
	{
		shlvl = ft_atoi(value);
		shlvl = shlvl == 2147483647 ? -1 : shlvl;
		shlvl = shlvl < 0 ? 0 : shlvl + 1;
		if (!(tmp = ft_itoa(shlvl)))
			clean_exit(1, MALLOC_ERR);
		set_env_var("SHLVL", tmp, env);
		ft_memdel((void*)&tmp);
	}
	else
		set_env_var("SHLVL", "1", env);
}
