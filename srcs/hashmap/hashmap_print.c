#include "hashmap.h"

void	print_hashmap(t_hashmap *hashmap)//REAL
{
	int			i;
	t_bool		is_empty;
	t_hash_item	*item_probe;

	i = -1;
	is_empty = 1;
	while (++i < (int)hashmap->size)
	{
		if (hashmap->items[i])
			is_empty = 0;
	}
	if (is_empty)
	{
		ft_printf("hash: hash table empty\n");
		return ;
	}
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

void	print_hashmap_l_args(t_hashmap *hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int			i;
	const char	*value;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		if ((value = check_hashmap(argv[i], hashmap, HASH_CHECK)))
			ft_printf("hash -p %s %s\n", value, argv[i]);
		else
			ft_dprintf(2, "hash: %s wasn't found\n", argv[i]);
	}
}

void	print_hashmap_l(t_hashmap *hashmap)
//void	print_hashmap_l(t_hashmap *hashmap, t_hash_args *hash_args, int argc,
//		char ** argv);
{
	int			i;
	t_hash_item	*item_probe;
	//t_bool is_empty;//to print hash table empty

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

void	hash_builtin_print(t_hashmap *hashmap, t_hash_args *hash_args, int argc, char **argv)//TODO change so L print only args(starting @ name_index)
{
	if (hash_args->opt & O_L)
	{
		if (!hash_args->name_index)
			print_hashmap_l(hashmap);//TODO:, hash_args);
		else
			print_hashmap_l_args(hashmap, hash_args, argc, argv);
	}
	else
		print_hashmap(hashmap);
}

void	print_usage(void)
{
	ft_dprintf(2, "hash [-lr] [-p pathname] [-d] [name ...]\n");//no 't'
}
