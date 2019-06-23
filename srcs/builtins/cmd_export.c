#include "ftsh.h"
#include "builtins.h"
#include "env.h"

static void		print_exported_vars(char **exported)
{
	int		i;
	char	*tmp;
	char	*name;

	i = 0;
	while (exported && exported[i])
	{
		name = get_name_from_varline(exported[i]);
		ft_printf("export %s=\"", name);
		tmp = ft_strchr(exported[i], '=');
		if (tmp)
			tmp = tmp + 1;
		if (tmp)
			ft_printf("%s", tmp);
		ft_printf("\"\n");
		ft_strdel(&name);
		i++;
	}
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

static void		export_parsing_loop(char **argv, t_vars *vars, int *ret, int i)
{
	char	*value;

	while (argv[i])
	{
		value = NULL;
		if (check_string_export(argv[i]))
		{
			ft_dprintf(2, "%s: export: `%s': ", SHELL_NAME, argv[i]);
			ft_dprintf(2, "not a valid identifier\n");
			*ret = 1;
		}
		else if (ft_strchr(argv[i], '=') && varline_case(argv[i], vars))
			*ret = 1;
		else if ((value = get_varline_value(argv[i], vars->shell_vars)))
		{
			add_variables(argv[i], value, &vars->env_save);
			add_variables(argv[i], value, &vars->env_vars);
			add_variables(argv[i], value, &vars->env_exported);
		}
		if (value)
			ft_strdel(&value);
		i++;
	}
}

int				case_export(char **argv, t_vars *vars)
{
	int		i;
	int		ret;

	i = 1;
	ret = parse_options_export(argv, &i);
	if (ret != 0 && ret != 1 && ret != 'p')
		return (export_usage(ret));
	else if (ret == 0)
		print_exported_vars(vars->env_exported);
	ret = 0;
	export_parsing_loop(argv, vars, &ret, i);
	return (ret);
}
