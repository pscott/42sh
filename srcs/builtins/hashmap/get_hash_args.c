#include "hashmap.h"
#include "builtins.h"

static void	init_hash_args(t_hash_args *hash_args)
{
	hash_args->opt = 0;
	hash_args->path = NULL;
	hash_args->name_index = 0;
	hash_args->state = get_opt;
}

/*
** is_arg_not_an_option
** just return (if  given arg is an option)
*/

static int	is_arg_not_an_option(char *arg, t_hash_args *hash_args)
{
	if ((arg[0] != '-' || (arg[0] == '-' && !arg[1]))
		&& hash_args->state == get_opt)
		return (1);
	return (0);
}

/*
** last_args_check
** just check at the end of parsing if every needed args was found
*/

static int	last_args_check(t_hash_state state)
{
	if (state == get_hash_path)
	{
		ft_dprintf(2, "hash: -p: option requires an argument\n");
		ft_dprintf(STDERR_FILENO,
				"hash usage [-lr] [-p pathname] [-d] [name ...]\n");
		return (0);
	}
	return (1);
}

/*
** get_hash_opt
** check if the given option are valid
** if not, print usage
*/

static int	get_hash_opt(char *arg, t_hash_args *hash_args)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'p' && arg[i + 1])
		{
			hash_args->path = &arg[i + 1];
			hash_args->state = get_name;
			return (1);
		}
		else if (arg[i] == 'p')
			hash_args->state = get_hash_path;
		else if (arg[i] == 'l')
			hash_args->opt = hash_args->opt | o_l;
		else if (arg[i] == 'd')
			hash_args->opt = hash_args->opt | o_d;
		else if (arg[i] == 'r')
			hash_args->opt = hash_args->opt | o_r;
		else
			return (print_hash_invalid_option(arg[i]));
	}
	return (1);
}

/*
** get_hash_args
** loop through argv and set the parser state accordingly
** return 1 if succesfull
** return 0 if it failed
*/

int			get_hash_args(char **argv, t_hash_args *hash_args)
{
	int			i;

	init_hash_args(hash_args);
	i = 0;
	while (argv[++i])
	{
		if (is_arg_not_an_option(argv[i], hash_args))
			hash_args->state = get_name;
		if (hash_args->state == get_name && !hash_args->name_index)
		{
			hash_args->name_index = i;
			hash_args->state = get_done;
		}
		else if (hash_args->state == get_hash_path)
		{
			hash_args->path = argv[i];
			hash_args->state = get_name;
		}
		else if (argv[i][0] == '-' && hash_args->state == get_opt)
		{
			if (!get_hash_opt(argv[i], hash_args))
				return (0);
		}
	}
	return (last_args_check(hash_args->state));
}
