#include "hashmap.h"

/*
** add_to_hashmap
** add key with value to hashmap
** replace old value if the same key if found
** set item->count to 0
** resize the hashmap if bucket list length > MAX_HASHMAP_COLLISION
*/

t_bool		add_to_hashmap(char *key, char *value, t_hashmap **hashmap)
{
	unsigned int	index;
	t_hash_item		*item_probe;
	t_hash_item		*prev_probe;
	int				list_len;

	//ft_printf("adding {%s} to hashmap\n", key);
	index = hashfun(key) % (*hashmap)->size;
	item_probe = (*hashmap)->items[index];
	prev_probe = NULL;
	list_len = 0;
	while (item_probe && ft_strcmp(key, item_probe->key))
	{
		prev_probe = item_probe;
		item_probe = item_probe->next;
		list_len++;
	}
	if (item_probe)//	item found
	{
		replace_item(item_probe, value);//	protect
		return (1);
	}
	else//	item not found
	{
		if (!prev_probe)//	no linked item
		{
			if (!((*hashmap)->items[index] = create_new_item(key, value)))
				return (0);//ERROR_MEM;
		}
		else if (!(prev_probe->next = create_new_item(key, value)))//	i'm at the end of list
			return (0);//ERROR_MEM;
		if (list_len >= MAX_HASHMAP_COLLISION)
			*hashmap = resize_up_hashmap(*hashmap);
		return (1);
	}
}

/*
** check_hashmap
** return a pointer to the value corresponding to 'key'
** and modify the count according to 'opt'
** return NULL if 'key' wasn't found
*/

char	*check_hashmap(const char *key, t_hashmap *hashmap, t_hashopt opt)
{
	unsigned int	index;
	t_hash_item		*item_probe;

	//item_probe = hashmap->items[hashfun(key) % hashmap->size];//no need for index
	index = hashfun(key) % hashmap->size;
	item_probe = hashmap->items[index];
	while (item_probe)
	{
		if (!ft_strcmp(key, item_probe->key))
		{
			if (opt == hash_exec)
				item_probe->count++;
			else if (opt == hash_reset)
				item_probe->count = 0;
			return (item_probe->value);
		}
		item_probe = item_probe->next;
	}
	return (NULL);
}

void	print_usage(void)
{
	ft_dprintf(STDERR_FILENO, "hash [-lr] [-p pathname] [-d] [name ...]\n");
}
