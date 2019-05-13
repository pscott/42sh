#include "hashmap.h"
#include "execution.h"

static void	init_hash_args(t_hash_args *hash_args)
{
	hash_args->opt = 0;
	hash_args->path = NULL;
	hash_args->name_index = 0;
	hash_args->state = GET_OPT;
}

/*
** get_hash_opt
**
*/

static t_bool	get_hash_opt(char *arg, t_hash_args *hash_args)
{
	int	i;

	//if (!arg[1])//useless now that i check this in get_hash_args ??
	//{
	//	ft_printf("an - alone\n");
	//	hash_args->state = GET_NAME;
	//}
	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'p')
		{
			if (arg[i + 1])
			{
				hash_args->path = &arg[i + 1];
				hash_args->state = GET_NAME;
				return (1);
			}
			else
				hash_args->state = GET_PATH;
		}
		else if (arg[i] == 'l')
			hash_args->opt = hash_args->opt | O_L;
		else if (arg[i] == 'd')
			hash_args->opt = hash_args->opt | O_D;
		else if (arg[i] == 'r')
			hash_args->opt = hash_args->opt | O_R;
		else
		{
			ft_dprintf(2, "-%c: invalid option\n", arg[i]);
			print_usage();
			return (0);
		}
	}
	return (1);
}

static t_bool	get_hash_args(char **argv, t_hash_args *hash_args)
{
	int			i;

	init_hash_args(hash_args);
	i = 0;
	while (argv[++i])
	{
		if ((argv[i][0] != '-' || (argv[i][0] == '-' && !argv[i][1])) && hash_args->state == GET_OPT)
			hash_args->state = GET_NAME;
		if (hash_args->state == GET_NAME && !hash_args->name_index)
		{
			hash_args->name_index = i;
			hash_args->state = GET_DONE;
		}
		else if (hash_args->state == GET_PATH)
		{
			hash_args->path = argv[i];
			hash_args->state = GET_NAME;
		}
		else if (argv[i][0] == '-' && hash_args->state == GET_OPT)
		{
			if (!get_hash_opt(argv[i], hash_args))
				return (0);//error
		}
	}
	if (hash_args->state == GET_PATH)
	{
		ft_dprintf(2, "hash: -p: option requires an argument\n");//test
		print_usage();
		return (0);///error
	}
	return (1);//succes
}

/*
static void	add_each_name(t_hashmap **hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int		i;
	char	*value;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		//value = search in path;
		value = get_cmd_path(argv[0], //ICICICICICI PATH
		value = ft_strdup("tmp_path");//tmp
		add_to_hashmap(argv[i], value, hashmap);
	}
}
*/

static char	**get_paths(char **env)
{
	char	**paths;
	char	*path_line;

	if (!(path_line = get_envline_value("PATH", env)))
		ft_dprintf(2, "PATH not found\n");//tmp
	if (!(paths = ft_strsplit(path_line, ":")))
		ERROR_MEM;
	return (paths);
}

static void	add_each_name(t_vars *vars, t_hash_args *hash_args, int argc, char **argv)
{
	int		i;
	char	*value;
	char	**paths;

	i = hash_args->name_index - 1;
	if (!(paths = get_paths(vars->env_vars)))
		ERROR_MEM;//ERROR_MEM??pas sure
	while (++i < argc)
	{
		if (!(value = find_path(argv[i], paths)))
			ft_dprintf(2, "hash: %s: not found\n", argv[i]);
		else
			add_to_hashmap(argv[i], value, &vars->hashmap);
	}
}

static void	add_each_name_with_path(t_hashmap **hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int		i;

	i = hash_args->name_index - 1;
	while (++i < argc)
		add_to_hashmap(argv[i], hash_args->path, hashmap);
}

static void	pop_each_name(t_hashmap **hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int	i;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		if (!pop_hashmap_item(argv[i], *hashmap))
			ft_dprintf(2, "hash: %s: not found\n", argv[i]);
	}
}

//L only matter when printing
//make 'hash -l ls' same as 'hash -t ls'
//p>d (if name)
int			hash_builtin(t_vars *vars, int argc, char **argv)
{
	t_hash_args	hash_args;

	if (argc == 1)
	{
		print_hashmap(vars->hashmap);
		return (0);
	}
	if (!get_hash_args(argv, &hash_args))
		return (0);
	if (hash_args.opt & O_R)//priority
		reset_hashmap(&vars->hashmap);
	if (hash_args.path && hash_args.name_index)
		add_each_name_with_path(&vars->hashmap, &hash_args, argc, argv);
	else if (hash_args.opt & O_D && hash_args.name_index)
		pop_each_name(&vars->hashmap, &hash_args, argc, argv);
	else if ((!hash_args.opt || hash_args.opt & O_R) && hash_args.name_index)//test !opt, seems good
		add_each_name(vars, &hash_args, argc, argv);
	else if (!(hash_args.opt & O_R))//test, seems good
		hash_builtin_print(vars->hashmap, &hash_args, argc, argv);
	return (0);
}
