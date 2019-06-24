#include "auto_completion.h"
#include "env.h"

int				is_same_char(char a, char b)
{
	if (a == b)
		return (1);
	if (a <= 'Z' && a >= 'A' && a + 32 == b)
		return (1);
	if (a <= 'z' && a >= 'a' && a - 32 == b)
		return (1);
	return (0);
}

int				get_path(char ***path, t_vars *vars)
{
	char		*tmpath;

	if (!vars || !vars->env_vars)
		return (0);
	if (!(tmpath = get_envline_value("PATH", vars->env_vars)))
	{
		*path = NULL;
		return (1);
	}
	if (!(*path = ft_strsplit(tmpath, ":")))
		clean_exit(1, 1);
	return (0);
}

int				free_two_strings(char **s1, char **s2)
{
	if (s1)
		ft_strdel(s1);
	if (s2)
		ft_strdel(s2);
	return (0);
}

int				free_four_strings(char **s1, char **s2, char **s3, char **s4)
{
	free_two_strings(s1, s2);
	free_two_strings(s3, s4);
	return (0);
}
