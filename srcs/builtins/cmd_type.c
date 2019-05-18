#include "42sh.h"
#include "execution.h"
#include "builtins.h"

/*
**	Returns 0 if it succesfully executed. Else returns 1.
*/

int		case_type(char **argv, t_vars *vars)
{
	unsigned int	i;
	char			*path;
	int				ret;

	if (!argv[1])//if (argc < 2);
		return (0);
	ret = 0;
	i = 0;
	while (argv[++i])//while (++i < argc)
	{
		//checktype
		if (check_builtins(&argv[i]))
			ft_printf("%s is a shell builtin\n", argv[i]);
		else if ((path = check_hashmap(argv[i], vars->hashmap, hash_check)))
			ft_printf("%s is hashed (%s)\n", argv[i], path);
		//else if ((path = type_get_cmd_path(argv[i], vars->env_vars)))
		else if ((path = get_cmd_path(&argv[i], vars->env_vars)))
			ft_printf("%s is %s\n", argv[i], path);
		else
			ret = 1;
	}
	return (0);
}
