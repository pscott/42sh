#include "ftsh.h"
#include "history.h"

// debug function

int		case_history(char **argv)
{
	int				fd;
	t_vars			*vars;
	t_hist_lst		*hist_lst;
	t_st_cmd		*st_cmd;
	char			*tmp;
	int				i;
	
	vars = get_vars(NULL);
	tmp = NULL;
//	ft_dprintf(2, "%s, %s", argv[0], argv[1]);
	if (argv && argv[0] && argv[1] && !ft_strcmp(argv[1], "--file"))
	{
		if ((fd = open_history((const char **)vars->env_vars, O_RDONLY | O_NOFOLLOW)) > 0)
		{
			while (get_next_line(fd, &tmp) > 0 && tmp)
				ft_printf("%s\n", tmp);
		}
	}
	else
	{
		i = -1;
		st_cmd = get_st_cmd(NULL);
		hist_lst = get_begin_lst(st_cmd->hist_lst);
		if (hist_lst->next)
		{
			while (hist_lst->next->next)
			{
				ft_printf("%d\t%s", ++i, hist_lst->txt);
				hist_lst = hist_lst->next;
			}
		}
	}
	return (0);
}
