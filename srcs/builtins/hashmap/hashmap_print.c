#include "hashmap.h"

static int	is_hashmap_empty(t_hashmap *hashmap)
{
	int	is_empty;
	int	i;

	is_empty = 1;
	i = -1;
	while (++i < (int)hashmap->size)
	{
		if (hashmap->items[i])
			is_empty = 0;
	}
	if (is_empty)
		ft_dprintf(STDERR_FILENO, "hash: hash table empty\n");
	return (is_empty);
}

void		print_hashmap(t_hashmap *hashmap)
{
	int			i;
	t_hash_item	*item_probe;

	if (is_hashmap_empty(hashmap))
		return ;
	ft_dprintf(STDOUT_FILENO, "hits\tcommand\n");
	i = -1;
	while (++i < hashmap->size)
	{
		item_probe = hashmap->items[i];
		while (item_probe)
		{
			ft_dprintf(STDOUT_FILENO, "%4d\t%s\n",
				item_probe->count, item_probe->value);
			item_probe = item_probe->next;
		}
	}
}

int			print_hashmap_l_args(t_hashmap *hashmap, t_hash_args *hash_args,
			int argc, char **argv)
{
	int			i;
	const char	*value;
	int			ret;

	i = hash_args->name_index - 1;
	ret = 0;
	while (++i < argc)
	{
		if ((value = check_hashmap(argv[i], hashmap, hash_check)))
			ft_dprintf(STDOUT_FILENO, "hash -p %s %s\n", value, argv[i]);
		else
		{
			ft_dprintf(STDERR_FILENO, "hash: %s: not found\n", argv[i]);
			ret = 1;
		}
	}
	return (ret);
}

void		print_hashmap_l(t_hashmap *hashmap)
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
			ft_dprintf(STDOUT_FILENO, "hash -p %s %s\n",
				item_probe->value, item_probe->key);
			item_probe = item_probe->next;
		}
	}
}

int			hash_builtin_print(t_hashmap *hashmap, t_hash_args *hash_args,
			int argc, char **argv)
{
	if (hash_args->opt & o_l)
	{
		if (!hash_args->name_index)
			print_hashmap_l(hashmap);
		else
			return (print_hashmap_l_args(hashmap, hash_args, argc, argv));
	}
	else
		print_hashmap(hashmap);
	return (0);
}
