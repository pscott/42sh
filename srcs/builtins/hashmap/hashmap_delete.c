#include "hashmap.h"

static void		delete_hashmap_item(t_hash_item *item)
{
	ft_memdel((void*)&item->key);
	ft_memdel((void*)&item->value);
	ft_memdel((void*)&item);
}

/*
** delete_hashmap
** free the whole hashmap
*/

void		delete_hashmap(t_hashmap *hashmap)
{
	int			i;
	t_hash_item	*item_probe;
	t_hash_item	*prev_probe;

	i = -1;
	while (++i < (int)hashmap->size)
	{
		if (hashmap->items[i])
		{
			item_probe = hashmap->items[i];
			while (item_probe)
			{
				prev_probe = item_probe;
				item_probe = item_probe->next;
				delete_hashmap_item(prev_probe);
			}
		}
	}
	ft_memdel((void*)&hashmap->items);
	ft_memdel((void*)&hashmap);
}

/*
** replace_item
** substitute the given item value by a new one
** and set count to 0
*/

void		replace_item(t_hash_item *item, const char *value)
{
	if (!ft_strcmp(value, item->value))
		item->count = 0;
	else
	{
		ft_memdel((void*)&item->value);
		if (!(item->value = ft_strdup(value)))
			return ;//ERROR_MEM;
		item->count = 0;
	}
}

/*
** pop_hashmap_item
** delete the item linked to the given 'key'
** without breaking the linked list if there's one
*/

t_bool		pop_hashmap_item(const char *key, t_hashmap *hashmap)//useless bool ?
{
	size_t	index;
	t_hash_item	*item_probe;
	t_hash_item	*prev_probe;

	if (!check_hashmap(key, hashmap, hash_check))//dangerous to base on this ?
		return (0);
	index = hashfun(key) % hashmap->size;
	item_probe = hashmap->items[index];
	prev_probe = NULL;
	while (item_probe && ft_strcmp(key, item_probe->key))//checking item_probe useless cause i check_hashmap before
	{
		prev_probe = item_probe;
		item_probe = item_probe->next;
	}
	if (prev_probe)//	item not the first of the list
		prev_probe->next = item_probe->next;
	else//	item is first of the list
		hashmap->items[index] = item_probe->next;
	delete_hashmap_item(item_probe);
	return (1);
}

t_bool		reset_hashmap(t_hashmap **hashmap)
{
	t_hashmap	*new_map;

	delete_hashmap(*hashmap);
	if (!(new_map = init_hashmap(INIT_HASH_SIZE)))
		return (0);//ERROR_MEM;
	*hashmap = new_map;
	return (1);
}
