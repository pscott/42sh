#include "hashmap.h"

static t_bool	is_hashmap_empty(t_hashmap *hashmap)
{
	t_bool	is_empty;
	int		i;

	is_empty = 1;
	i = -1;
	while (++i < (int)hashmap->size)
	{
		if (hashmap->items[i])
			is_empty = 0;
	}
	if (is_empty)
		ft_printf("hash: hash table empty\n");
	return (is_empty);
}

void	print_hashmap(t_hashmap *hashmap)
{
	int			i;
	t_hash_item	*item_probe;

	if (is_hashmap_empty(hashmap))
		return ;
	ft_printf("hits\tcommand\n");
	i = -1;
	while (++i < (int)hashmap->size)
	{
		item_probe = hashmap->items[i];
		while (item_probe)
		{
			ft_printf("%4d\t%s\n", item_probe->count, item_probe->value);
			item_probe = item_probe->next;
		}
	}
}

void	print_hashmap_l_args(t_hashmap *hashmap, t_hash_args *hash_args
		, int argc, char **argv)//need t_bool
{
	int			i;
	const char	*value;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		if ((value = check_hashmap(argv[i], hashmap, HASH_CHECK)))
			ft_printf("hash -p %s %s\n", value, argv[i]);
		else
			ft_dprintf(2, "hash: %s: not found\n", argv[i]);
	}
}

void	print_hashmap_l(t_hashmap *hashmap)
{
	int			i;
	t_hash_item	*item_probe;

	if (is_hashmap_empty(hashmap))
		return ;
	i = -1;
	while (++i < (int)hashmap->size)
	{
		item_probe = hashmap->items[i];
		while (item_probe)
		{
			ft_printf("hash -p %s %s\n", item_probe->value, item_probe->key);
			item_probe = item_probe->next;
		}
	}
}

void	hash_builtin_print(t_hashmap *hashmap, t_hash_args *hash_args
		, int argc, char **argv)
{
	if (hash_args->opt & O_L)
	{
		if (!hash_args->name_index)
			print_hashmap_l(hashmap);
		else
			print_hashmap_l_args(hashmap, hash_args, argc, argv);
	}
	else
		print_hashmap(hashmap);
}

void	print_usage(void)
{
	ft_dprintf(2, "hash [-lr] [-p pathname] [-d] [name ...]\n");
}
