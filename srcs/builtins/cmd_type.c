#include "builtins.h"
#include "execution.h"
#include "hashmap.h"

static void			print_error(const char *arg)
{
	ft_dprintf(2, SHELL_NAME);
	ft_dprintf(2, ": type: %s: not found\n", arg);
}

/*
**	Returns 0 if it succesfully executed. Else returns 1.
*/

int					case_type(char **argv, t_vars *vars)
{
	unsigned int	i;
	char			*path;
	int				ret;

	if (!argv[1])
		return (0);
	ret = 0;
	i = 0;
	while (argv[++i])
	{
		if (check_builtins(&argv[i]))
			ft_printf("%s is a shell builtin\n", argv[i]);
		else if ((path = check_hashmap(argv[i], vars->hashmap, hash_check)))
			ft_printf("%s is hashed (%s)\n", argv[i], path);
		else if ((path = get_cmd_path(&argv[i], vars->env_vars, 0)))
			ft_printf("%s is %s\n", argv[i], path);
		else
		{
			print_error(argv[i]);
			ret = 1;
		}
	}
	return (ret);
}
