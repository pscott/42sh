#include "hashmap.h"

void	populate_hashmap(t_hashmap **hashmap)
{
	//add_to_hashmap("1", "/bin/1", hashmap);
	//add_to_hashmap("2", "/bin/2", hashmap);
	//add_to_hashmap("3", "/bin/3", hashmap);
	//add_to_hashmap("4", "/bin/4", hashmap);
	//add_to_hashmap("5", "/bin/5", hashmap);
	//add_to_hashmap("6", "/bin/6", hashmap);
	//add_to_hashmap("7", "/bin/7", hashmap);
	//add_to_hashmap("8", "/bin/8", hashmap);
	//add_to_hashmap("9", "/bin/9", hashmap);
	//add_to_hashmap("10", "/bin/10", hashmap);
	//add_to_hashmap("11", "/bin/11", hashmap);
	//add_to_hashmap("12", "/bin/12", hashmap);
	//add_to_hashmap("13", "/bin/13", hashmap);
	//add_to_hashmap("14", "/bin/14", hashmap);
	//add_to_hashmap("15", "/bin/15", hashmap);
	//add_to_hashmap("16", "/bin/16", hashmap);
	//add_to_hashmap("17", "/bin/17", hashmap);
	//add_to_hashmap("18", "/bin/18", hashmap);
	//add_to_hashmap("19", "/bin/19", hashmap);
	//add_to_hashmap("20", "/bin/20", hashmap);
	//add_to_hashmap("21", "/bin/21", hashmap);
	//add_to_hashmap("22", "/bin/22", hashmap);
	add_to_hashmap("ls", "/bin/ls", hashmap);
	add_to_hashmap("cat", "/bin/cat", hashmap);
}

int		main(int argc, char **argv, char **env)
{
	t_hashmap	*hashmap;

	(void)env;
	//if (!(hashmap = init_hashmap(INIT_HASH_SIZE)))
	if (!(hashmap = init_hashmap(3)))
	{
		ft_dprintf(2, "init_hashmap returned NULL\n");
		return (1);
	}
	populate_hashmap(&hashmap);
	//print_hashmap(hashmap);

	//const char	*path;
	//if ((path = check_hashmap("ls", hashmap, HASH_EXEC)))
	//	printf("exec ls @ %s\n", path);
	//else
	//	printf("ls not found in hashmap\n");
	//
	printf("(main)hash_builtin\n");
	printf("%s\n", argv[1]);
	hash_builtin(&hashmap, argc, argv, env);
	printf("(main)hash_builtin END\n");
	//
	//print_hashmap(hashmap);


	printf("(main)delete_hashmap\n");
	delete_hashmap(hashmap);
	return (0);
}
