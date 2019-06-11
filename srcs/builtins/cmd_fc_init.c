#include "ftsh.h"
#include "builtins.h"

void			print_usage_fc(void)
{
	int			fd;

	fd = STDERR_FILENO;
	ft_dprintf(fd, "fc: usage:\n");
	ft_dprintf(fd, "    fc [-r] [-e editor] [first [last]]\n");
	ft_dprintf(fd, "OR  fc -l [-nr] [first [last]]\n");
	ft_dprintf(fd, "OR  fc -s [old=new] [first]");
}

int				error_fc(char *s, int i, int type)
{
	if (type == invalid_option)
	{
		ft_dprintf(STDERR_FILENO, "fc: -%c: invalid option\n", s[i]);
	}
	else if (type == invalid_mix)
	{
		ft_dprintf(STDERR_FILENO, "fc: %s: invalid option mix\n", s);
	}
	print_usage_fc();
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

static int		is_valid_and_valuable_mix(char flag[4], char c)
{
	if (ft_strchr(flag, c))
		return (0);//opti depending on how flags interact
	if (c != 's' && ft_strchr(flag, 's'))
		return (-1);
	if (c == 'e' && (ft_strchr(flag, 'l') || ft_strchr(flag, 'n')))
		return (-1);
	if (c == 's' &&  flag[0] != '.')
		return (-1);
	if (c == 'e' && (ft_strchr(flag, 'l') || ft_strchr(flag, 'n')
			|| ft_strchr(flag, 's')))
		return (-1);
	if (c == 'l' && ft_strchr(flag, 'e'))
		return (-1);
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
	int			is_val;

	i = 0;
	while (argv[++i] && !ft_strncmp(argv[i], "--", 3))
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			k = -1;
			while (argv[i][++j])
			{
				if (!is_valid_option(argv[i][j]))
					return (error_fc(argv[i], j, invalid_option));//return error directement
				if (((is_val = is_valid_and_valuable_mix(st_fc->flag, argv[i][j]))) == 1)
					st_fc->flag[++k] = argv[i][j];
				else if (is_val == -1)
					return (error_fc(argv[i], j, invalid_mix));
			}
		}
	}
	if (argv[i])// is argv[i] == "--" ? 
		i--;
	return (i);
}
/*
int				fc_parse_operands(t_st_fc *st_fc, char **args, int i)
{

}
*/
int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			start_operand;

	i = 5;
	(void)st_cmd;
	while (--i > -1)
		(*st_fc).flag[i] = '.';
	start_operand = fc_parse_flags(st_fc, argv);
//	fc_parse_operands(st_fc, argv, start_operand);
	ft_printf("\nindex : %d, flags : %s", start_operand, st_fc->flag);
	sleep(1);
	return (0);
}
