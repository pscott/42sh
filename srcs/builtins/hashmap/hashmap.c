#include "hashmap.h"

static void	move_on_bucket_list(t_hash_item **item_probe
			, t_hash_item **prev_probe, unsigned int *list_len)
{
	*prev_probe = *item_probe;
	*item_probe = (*item_probe)->next;
	(*list_len)++;
}

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
	unsigned int	list_len;

	index = hashfun(key) % (*hashmap)->size;
	item_probe = (*hashmap)->items[index];
	prev_probe = NULL;
	list_len = 0;
	while (item_probe && ft_strcmp(key, item_probe->key))
		move_on_bucket_list(&item_probe, &prev_probe, &list_len);
	if (item_probe)//item found
		return (replace_item(item_probe, value));
	//	item not found
	if (!prev_probe)//	no linked item
	{
		if (!((*hashmap)->items[index] = create_new_item(key, value)))
			return (0);//ERROR_MEM ?? should i ERROR_MEM in create_new_item so i can ignore return value here ?
	}
	else if (!(prev_probe->next = create_new_item(key, value)))//	i'm at the end of list
		return (0);//ERROR_MEM;
	if (list_len >= MAX_HASHMAP_COLLISION)
		*hashmap = resize_up_hashmap(*hashmap);
	return (1);
}

/*
** check_hashmap
** return a pointer to the value corresponding to 'key'
** and modify the count according to 'opt'
** return NULL if 'key' wasn't found
*/

char		*check_hashmap(const char *key, t_hashmap *hashmap, t_hashopt opt)
{
	t_hash_item		*item_probe;

	item_probe = hashmap->items[hashfun(key) % hashmap->size];
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
