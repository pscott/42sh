#include "tosh.h"
//TODO DELETE ME

/*
** my_strtrim protect the strndup use in add_to_cmdlist
*/

char		*my_strtrim(char *str)
{
	int		i;
	char	*tmp;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
		if (str[i] == 0)
			return (NULL);
	}
	tmp = &str[i];
	i = ft_strlen(tmp) - 1;
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i--;
	res = ft_strndup(tmp, i + 1);
	printf("in strtrim: {%s}, i=%d\n", res, i);
	return (res);
}

/*
** create_cmdlst
** create a new cmdlst
** trim and FREE the cmdline
** return a pointer to the head node
*/

static t_cmdlst	*create_cmdlst_head(char *cmdline)
{
	t_cmdlst	*new_node;

	ft_putendl("Creating new node");
	if (!(new_node = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
		return (NULL);
	if (!(new_node->cmdline = my_strtrim(cmdline)))
	{
		ft_memdel((void*)&cmdline);
		ft_memdel((void*)&new_node);
		return (NULL);
	}
	ft_memdel((void*)&cmdline);
	new_node->next = NULL;
	return (new_node);
}

/*
** add_to_cmdlst
** append a new nodei containing the cmdline to the list pointed by cmdlst_head
** trim and FREE the cmdline
** return 1 on success
** return 0 otherwise
*/

int			add_to_cmdlst(char *cmdline, t_cmdlst **cmdlst_head)
{
	t_cmdlst	*new_node;
	t_cmdlst	*probe;

	if (!cmdlst_head || !cmdline)
	{
		return (0);
	}
	if (!(*cmdlst_head))
	{
		if (!(*cmdlst_head = create_cmdlst_head(cmdline)))
			return (0);
		return (1);
	}
	ft_putendl("Adding new node");
	if (!(new_node = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
		return (0);
	if (!(new_node->cmdline = my_strtrim(cmdline)))
	{
		ft_memdel((void*)&new_node);
		return (0);
	}
	ft_memdel((void*)&cmdline);
	probe = *cmdlst_head;
	while (probe->next)
		probe = probe->next;
	probe->next = new_node;
	new_node->next = NULL;
	return (1);
}

void		print_cmdlst(t_cmdlst *head)//for debug
{
	t_cmdlst	*probe;

	if (!head)
	{
		ft_putendl("nothing to print");
		return ;
	}
	probe = head;
	while (probe->next)
	{
		printf("{%s}\n", probe->cmdline);//TODO
		probe = probe->next;
	}
	printf("{%s}\n", probe->cmdline);
}
