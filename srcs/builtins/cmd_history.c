#include "ftsh.h"
#include "history.h"

int		case_history(char **argv)
{
	int		fd;
	t_vars	*vars;
	char	*tmp;

	(void)argv;
	vars = get_vars(NULL);
	tmp = NULL;
			ft_dprintf(2,"HERE");
	if ((fd = open_history((const char **)vars->env_vars, O_RDONLY | O_NOFOLLOW)) > 0)
	{
		while (get_next_line(fd, &tmp) > 0 && tmp)
		{
			ft_printf("%s\n", tmp);
		}
	}
	return (0);
}
