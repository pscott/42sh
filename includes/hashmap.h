#ifndef HASHMAP_H
# define HASHMAP_H

# include "ftsh.h"
# include "libft.h"

/*
**	INIT_HASH_SIZE needs to be prime to make it work
*/

# define INIT_HASH_SIZE 7
# define MAX_HASHMAP_COLLISION 3
# define TRUE 1
# define FALSE 0

typedef struct			s_hash_item
{
	char				*key;
	char				*value;
	size_t				count;
	struct s_hash_item	*next;
}						t_hash_item;

typedef struct			s_hashmap
{
	size_t				size;
	t_hash_item			**items;

}						t_hashmap;

typedef struct			s_hash_args
{
	unsigned char		opt;
	char				*path;
	unsigned int		name_index;
	unsigned char		state;
}						t_hash_args;

typedef enum			e_hash_opt
{
	o_l = 0B1,
	o_d = 0B10,
	o_r = 0B100
}						t_hash_opt;

typedef enum			e_hash_state
{
	get_opt,
	get_hash_path,
	get_name,
	get_done
}						t_hash_state;

/*
** t_hashopt
** give check_hashmap() intructions for modifying the count
*/

typedef enum			e_hashopt
{
	hash_check,
	hash_exec,
	hash_reset
}						t_hashopt;

void					delete_hashmap(t_hashmap *hashmap);
int					add_to_hashmap(char *key, char *value,
						t_hashmap **hashmap);
unsigned int			hashfun(const char *input);
char					*check_hashmap(const char *key, t_hashmap *hashmap,
						t_hashopt opt);

/*
** hashmap_print.c
*/
void					print_hashmap(t_hashmap *hashmap);
void					print_hashmap_l(t_hashmap *hashmap);
void					print_hash_usage(void);
int					print_hashmap_l_args(t_hashmap *hashmap,
						t_hash_args *hash_args, int argc, char **argv);
int					hash_builtin_print(t_hashmap *hashmap,
						t_hash_args *hash_args, int argc, char **argv);

/*
** hashmap_alloc.c
*/

t_hash_item				*create_new_item(const char *key, const char *value);
t_hashmap				*init_hashmap(size_t size);
t_hashmap				*resize_up_hashmap(t_hashmap *old_map);
t_hashmap				*resize_down_hashmap(t_hashmap *old_map);
void					cpy_hashmap(t_hashmap *old_map, t_hashmap **new_map);

/*
** hashmap_delete.c
*/

void					delete_hashmap(t_hashmap *hashmap);
int					replace_item(t_hash_item *item, const char *value);
int					pop_hashmap_item(const char *key, t_hashmap *hashmap);
int					reset_hashmap(t_hashmap **hashmap);

/*
** prime.c
*/

unsigned int			find_next_prime(unsigned int nb);
unsigned int			find_prev_prime(unsigned int nb);

/*
** hashmap_errors.c
*/

int					print_hash_invalid_option(char c);

/*
** hash_main.c
*/

int						hash_builtin(t_vars *vars, int argc, char **argv);
int					get_hash_args(char **argv, t_hash_args *hash_args);

#endif
