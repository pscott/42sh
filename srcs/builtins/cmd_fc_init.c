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

int				error_fc(char *s, int i, int type, t_st_fc *st_fc)
{
	int			len;

	ft_dprintf(STDERR_FILENO, "fc: -");
	if (type == invalid_option)
	{
		ft_dprintf(STDERR_FILENO, "%c: invalid option\n", s[i]);
	}
	else if (type == invalid_mix)
	{
		len = ft_strlen_char(st_fc->flag, '.');
		st_fc->flag[len] = s[i];
		write(STDERR_FILENO, st_fc->flag, len + 1);
		ft_dprintf(STDERR_FILENO, ": invalid mix\n");
	}
	print_usage_fc();
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
	while (argv[++i] && ft_strncmp(argv[i], "--", 3))
	{
		if (argv[i][0] == '-')
		{
			j = 0;
			k = -1;
			while (argv[i][++j])
			{
				if (!is_valid_option(argv[i][j]))
					return (error_fc(argv[i], j, invalid_option, st_fc));//return error directement
				if (((is_val = is_valid_and_valuable_mix(st_fc->flag, argv[i][j]))) == 1)
					st_fc->flag[++k] = argv[i][j];
				else if (is_val == -1)
					return (error_fc(argv[i], j, invalid_mix, st_fc));
			}
		}
	}
	if (argv[i])// is argv[i] == "--" ? 
		i--;
	ft_printf("\nindex : %d, flags : %s", i, st_fc->flag);
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
	sleep(1);
	return (0);
}
