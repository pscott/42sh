#include "ftsh.h"
#include "builtins.h"

int				error_fc(char c, int type)
{
	if (type == invalid_option)
	{
		ft_dprintf(STDERR_FILENO, "fc: -%c: invalid option\n", c);
	}
	ft_dprintf(STDERR_FILENO, "fc: usage: fc [-e name] [-lnr] [first] [last] ");
	ft_dprintf(STDERR_FILENO, "or fc -s [pat=rep] [command]");
	return (1);
}

static int		is_valid_option(char c)
{
	if (ft_strchr("selnr", c))
		return (1);
	return (0);
}

static int		is_new_or_important_option(char flag[4], char c)
{
	if (ft_strchr(flag, c))
		return (0);//opti depending on how flags interact
	if (c != 's' && ft_strchr(flag, 's'))
		return (0);
	if (c == 'l' && ft_strchr(flags, 'e'))
		return (0);
	return (1);
}

static int		fc_parse_flags(t_st_fc *st_fc, char **argv)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	while (argv[++i] && !ft_strequ(argv[i], "--"))
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			k = -1;
			while (argv[i][++j])
			{
				if (!is_valid_option(argv[i][j]))
					return (error_fc(argv[i][j], invalid_option));
				if (is_new_or_important_option(st_fc->flags, argv[i][j]))
					st_fc->flags[++k] = argv[i][j];
			}
		}
	}
	if (argv[i])
		i--;
	ft_dprintf(2,"%s",  st_fc->flags);
	return (i);
}

int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			index_arg;

	i = 5;
	while (--i > -1)
		(*st_fc).flags[i] = '.';
	index_arg = fc_parse_flags(st_fc, argv);
	return (0);
}
