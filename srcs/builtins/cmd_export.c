#include "ftsh.h"
#include "builtins.h"
#include "env.h"

static void		print_exported_vars(char **exported)
{
	int		i;
	char	*tmp;

	i = 0;
	while (exported && exported[i])
	{
		ft_printf("export %s=\"", get_name_from_varline(exported[i]));
		tmp = ft_strchr(exported[i], '=');
		if (tmp)
			tmp = tmp + 1;
		if (tmp)
			ft_printf("%s", tmp);
		ft_printf("\"\n");
		i++;
	}
}

static int		parse_options_export(char **argv, int *i)
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

static int		check_string_export(char *str)
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

static int		export_usage(char c)
{
	ft_dprintf(2, "%s: export: -%c: invalid option\n", SHELL_NAME, c);
	ft_dprintf(2, "export: usage: export [name[=value] ...] or export -p\n", c);
	return (1);
}

/*
** varline_case
** is call if an export argument looks like this: 'toto=tata'
*/

static int		varline_case(char *argv, t_vars *vars)
{
	if (vars->env_save)
		add_varline(argv, &vars->env_save);
	else
		add_varline(argv, &vars->env_vars);
	add_varline(argv, &vars->shell_vars);
	add_varline(argv, &vars->env_exported);
	return (0);
}

int				case_export(char **argv, t_vars *vars)
{
	int		i;
	char	*value;
	int		ret;
	int		print;

	i = 1;
	ret = 0;
	print = parse_options_export(argv, &i);
	if (print != 0 && print != 1 && print != 'p')
		return (export_usage(print));
	else if (print == 0)
		print_exported_vars(vars->env_exported);
	while (argv[i])
	{
		value = NULL;
		if (check_string_export(argv[i]))
		{
			ft_dprintf(2, "%s: export: `%s': ", SHELL_NAME, argv[i]);
			ft_dprintf(2, "not a valid identifier\n");
			ret = 1;
		}
		else if (ft_strchr(argv[i], '=') && varline_case(argv[i], vars))
			ret = 1;
		else if ((value = get_varline_value(argv[i], vars->env_vars)))
		{
			add_variables(argv[i], value, &vars->shell_vars);
			add_variables(argv[i], value, &vars->env_save);//test
			add_variables(argv[i], value, &vars->env_exported);
		}
		else if ((value = get_varline_value(argv[i], vars->shell_vars)))
		{
			add_variables(argv[i], value, &vars->env_vars);
			add_variables(argv[i], value, &vars->env_exported);
		}
		if (value)
			ft_strdel(&value);
		i++;
	}
	return (ret);
}
