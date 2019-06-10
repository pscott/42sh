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
	if (!ft_strchr("selnr", c))
		return (0);
	return (1);

}

static int		is_valid_and_valuable_option(char flag[4], char c)
{
	if (ft_strchr(flag, c))
		return (0);//opti depending on how flags interact
	if (c != 's' && ft_strchr(flag, 's'))
		return (0);
	/*
	if (c == 'l' && ft_strchr(flags, 'e'))
		return (0);
		*/
	return (1);
}

/*
**	Parses FC flags, while preventing bad flag association.
**	Returns (1) if an error occurs.
**	Else, returns (i), the index of the first operand.
*/

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
				{
					error_fc(argv[i][j], invalid_option);//return error directement
					return (1);
				}
				if (is_valid_and_valuable_option(st_fc->flags, argv[i][j]))
					st_fc->flags[++k] = argv[i][j];
			}
		}
	}
	if (argv[i])// is argv[i] == "--" ? 
		i--;
	return (i);
}

int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			index_operand;

	i = 5;
	while (--i > -1)
		(*st_fc).flags[i] = '.';
	index_operand = fc_parse_flags(st_fc, argv);
	ft_printf("\nindex : %d, flags : %s", index_operand, st_fc->flags);
	sleep(1);
	return (0);
}
