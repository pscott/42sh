#include "auto_completion.h"

unsigned int		len_lst(t_auto_comp *lst)
{
	unsigned int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->prev != NULL)
		lst = lst->prev;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

unsigned int		get_max_len(t_auto_comp *match)
{
	t_auto_comp		*tmp;
	char			*save_max;
	unsigned int	max;

	if (!match)
		return (0);
	save_max = NULL;
	tmp = match;
	max = ft_strlen(tmp->name);
	while ((tmp = tmp->next))
	{
		if (ft_strlen(tmp->name) > max)
		{
			ft_strdel(&save_max);
			max = ft_strlen(tmp->name);
			if (!(save_max = ft_strdup(tmp->name)))
				clean_exit(1, 1);
		}
	}
	if (save_max && save_max[ft_strlen(save_max) - 1] != ' ')
		max++;
	ft_strdel(&save_max);
	return (max);
}

void				print_spaces(const char *s, unsigned int cols)
{
	unsigned int	len;
	unsigned int	count;
	char			*spaces;

	spaces = NULL;
	count = 0;
	len = ft_strlen(s);
	if (cols == 1)
	{
		while (++len < cols)
			count++;
	}
	else
	{
		while (len++ <= cols)
			count++;
	}
	if (count > 0 && !(spaces = (char *)malloc(sizeof(char) * (count + 1))))
		clean_exit(1, 1);
	spaces[count] = '\0';
	ft_memset(spaces, ' ', count);
	ft_putstr(spaces);
	ft_strdel(&spaces);
}

int					is_display(unsigned int count)
{
	char			c;

	ft_putchar('\n');
	ft_dprintf(OUTPUT_FD, "Display all %u possibilities? (y or n)", count);
	while (1)
	{
		read(0, &c, 1);
		if (c == 'n' || c == 'N' || c == 127)
			return (1);
		else if (c == 3)
			return (1);
		else if (c == 'y' || c == 'Y' || c == 32)
			return (0);
	}
}
