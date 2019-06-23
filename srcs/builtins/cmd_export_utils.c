#include "builtins.h"

int		parse_options_export(char **argv, int *i)
{
	int		opt;
	int		k;

	opt = 0;
	while (argv[*i] && argv[*i][0] == '-' && ft_strcmp(argv[*i], "--"))
	{
		if (argv[*i][0] == '-')
		{
			k = 1;
			while (argv[*i][k])
			{
				if (argv[*i][k] != 'p')
					return (argv[*i][k]);
				k++;
			}
		}
		(*i)++;
	}
	if (argv[*i] && argv[*i][0] == '-')
		*i += 1;
	else if (argv[*i])
		return (1);
	return (opt);
}

int		check_string_export(char *str)
{
	int		i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int		export_usage(char c)
{
	ft_dprintf(2, "%s: export: -%c: invalid option\n", SHELL_NAME, c);
	ft_dprintf(2, "export: usage: export [name[=value] ...] or export -p\n", c);
	return (1);
}
