#include "hashmap.h"

/*
** create_new_item
** malloc and return a mallocated hashmap item
*/

t_hash_item	*create_new_item(const char *key, const char *value)
{
	t_hash_item	*new_item;

	if (!(new_item = (t_hash_item*)malloc(sizeof(*new_item))))
		clean_exit(1, 1);
	else if (new_item)
	{
		if (!(new_item->key = ft_strdup(key)))
		{
			ft_memdel((void*)&new_item);
			clean_exit(1, 1);
		}
		if (!(new_item->value = ft_strdup(value)))
		{
			ft_memdel((void*)&new_item->key);
			ft_memdel((void*)&new_item);
			clean_exit(1, 1);
		}
		new_item->count = 0;
		new_item->next = NULL;
	}
	return (new_item);
}

/*
** init_hashmap
** malloc and return a new hashmap of the given size (i don't check if size is
** prime)
*/

t_hashmap	*init_hashmap(size_t size)
{
	t_hashmap	*new_table;
	int			i;

	if (!(new_table = (t_hashmap*)malloc(sizeof(*new_table))))
		clean_exit(1, 1);
	if (!(new_table->items =
			(t_hash_item**)malloc(sizeof(t_hash_item*) * size)))
	{
		ft_memdel((void*)&new_table);
		clean_exit(1, 1);
	}
	new_table->size = size;
	i = -1;
	while (++i < (int)new_table->size)
		new_table->items[i] = NULL;
	return (new_table);
}

/*
** resize_up_hashmap
** malloc a bigger hashmap by finding next prime size
** copy the old hashmap values in it
** and return the new hashmap
*/

t_hashmap	*resize_up_hashmap(t_hashmap *old_map)
{
	size_t		new_size;
	t_hashmap	*new_map;

	new_size = (size_t)find_next_prime(old_map->size);
	if (!(new_map = init_hashmap(new_size)))
		clean_exit(1, 1);
	cpy_hashmap(old_map, &new_map);
	delete_hashmap(old_map);
	return (new_map);
}

t_hashmap	*resize_down_hashmap(t_hashmap *old_map)
{
	size_t		new_size;
	t_hashmap	*new_map;

	new_size = (size_t)find_prev_prime(old_map->size);
	if (!(new_map = init_hashmap(new_size)))
		clean_exit(1, 1);
	cpy_hashmap(old_map, &new_map);
	delete_hashmap(old_map);
	return (new_map);
}

/*
** cpy_hashmap
** copy all item of old hashmap into the new one
*/

void		cpy_hashmap(t_hashmap *old_map, t_hashmap **new_map)
{
	int			i;
	t_hash_item	*item_probe;
	t_hash_item	*prev_probe;

	i = -1;
	while ((++i < (int)old_map->size) && (item_probe = old_map->items[i]))
	{
		while (item_probe)
		{
			prev_probe = item_probe;
			item_probe = item_probe->next;
			add_to_hashmap(prev_probe->key, prev_probe->value, new_map);
		}
	}
}
