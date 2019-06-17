#include "builtins.h"

static int		check_av_size(char **argv)
{
	int		i;
	int		ac;

	i = 1;
	ac = 0;
	while (argv[ac])
		ac++;
	while (argv[i] && !ft_strcmp(argv[i], "!"))
		i++;
	i--;
	return (ac - i);
}

static void		init_ints(int *i, int *k, int *inv)
{
	*i = 1;
	*k = 1;
	*inv = 0;
}

char			**check_inv(char **argv, int *inv)
{
	int		i;
	int		k;
	int		size;
	char	**newargv;

	init_ints(&i, &k, inv);
	size = check_av_size(argv);
	if (!(newargv = (char**)malloc(sizeof(char*) * (size + 1))))
		clean_exit(1, 1);
	if (!(newargv[0] = ft_strdup(argv[0])))
		clean_exit(1, 1);
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "!"))
			*inv += 1;
		else
			break ;
		i++;
	}
	while (argv[i])
		if (!(newargv[k++] = ft_strdup(argv[i++])))
			clean_exit(1, 1);
	newargv[size] = NULL;
	return (newargv);
}
