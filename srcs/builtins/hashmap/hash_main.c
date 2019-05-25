#include "hashmap.h"
#include "builtins.h"
#include "execution.h"

static char		**get_hash_paths(char **env)//no comment needed
{
	char	**paths;
	char	*path_line;

	if (!(path_line = get_envline_value("PATH", env)))
		return (NULL);
	if (!(paths = ft_strsplit(path_line, ":")))
		ERROR_MEM;
	return (paths);
}

/*
** add_each_name
** get PATH and split it
** for each ARG:
** - ignore builtins
** - look for it in PATH
** - add it to hashmap if found
*/

static t_bool	add_each_name(t_vars *vars, t_hash_args *hash_args, int argc
				, char **argv)
{
	int		i;
	t_bool	return_value;
	char	*value;
	char	**paths;

	return_value = 0;
	i = hash_args->name_index - 1;
	paths = get_hash_paths(vars->env_vars);//no need protect: MEM_ERR is checked before, i protected 'find_path()'
	while (++i < argc)
	{
		if (check_builtins(&argv[i]))
			continue ;
		if (!(value = find_path(argv[i], paths)))
		{
			ft_dprintf(2, "%s: hash: %s: not found\n", SHELL_NAME, argv[i]);
			return_value = 1;
		}
		else
			add_to_hashmap(argv[i], value, &vars->hashmap);
	}
	return (return_value);
}

/*
** add_each_name_with_path
** is for '-p' option
** add each ARG into hashmap with the given path
*/

static void		add_each_name_with_path(t_hashmap **hashmap
				, t_hash_args *hash_args, int argc, char **argv)
{
	int		i;

	i = hash_args->name_index - 1;
	while (++i < argc)
		add_to_hashmap(argv[i], hash_args->path, hashmap);
}

/*
** pop_each_name
** is for -d option
** try do remove each ARG from hashmap
** print an error for unfindable ARG
*/

static t_bool	pop_each_name(t_hashmap **hashmap, t_hash_args *hash_args
				, int argc, char **argv)
{
	int		i;
	t_bool	return_value;

	i = hash_args->name_index - 1;
	return_value = 0;
	while (++i < argc)
	{
		if (!pop_hashmap_item(argv[i], *hashmap))
		{
			ft_dprintf(2, "%s: hash: %s: not found\n", SHELL_NAME, argv[i]);
			return_value = 1;
		}
	}
	return (return_value);
}

/*
** hash_builtin
** is main hash_function
** -r option a full priority
*/

int				hash_builtin(t_vars *vars, int argc, char **argv)
{
	t_hash_args	hash_args;

	if (argc == 1)
	{
		print_hashmap(vars->hashmap);
		return (0);
	}
	if (!get_hash_args(argv, &hash_args))
		return (2);
	if (hash_args.opt & o_r)
		reset_hashmap(&vars->hashmap);
	if (hash_args.path && hash_args.name_index)
		add_each_name_with_path(&vars->hashmap, &hash_args, argc, argv);
	else if (hash_args.opt & o_d && hash_args.name_index)
		return (pop_each_name(&vars->hashmap, &hash_args, argc, argv));
	else if ((!hash_args.opt || hash_args.opt & o_r) && hash_args.name_index)
		return (add_each_name(vars, &hash_args, argc, argv));
	else if (!(hash_args.opt & o_r))
		return (hash_builtin_print(vars->hashmap, &hash_args, argc, argv));
	return (0);
}
