#include "ftsh.h"
#include "history.h"

static void		print_usage_fc(void)
{
	int			fd;

	fd = STDERR_FILENO;
	ft_dprintf(fd, "fc: usage:\n");
	ft_dprintf(fd, "    fc [-r] [-e editor] [first [last]]\n");
	ft_dprintf(fd, "OR  fc -l [-nr] [first [last]]\n");
	ft_dprintf(fd, "OR  fc -s [old=new] [first]");
}

int				error_fc(char *s, int i, int type, t_st_fc *st_fc)
{
	ft_dprintf(STDERR_FILENO, "%s: fc: ", SHELL_NAME);
	if (type == path_unspecified)//pas lieu d'etre si PATH hardset dans inter varz
		ft_dprintf(2, "-e: $PATH is not set: impossible to find editor '%s'\n", s);
	else if (type == cmd_not_found)
		ft_dprintf(2, "%s: command not found\n", s);
	print_usage_fc();
	return (-1);
}

int				error_fc_index(char *flag)
{
	t_st_cmd	*st_cmd;

	st_cmd = get_st_cmd(NULL);
	ft_dprintf(STDERR_FILENO, "%s: fc: ", SHELL_NAME);
	if (flag[0] == 's')
	{
		ft_dprintf(2, "no command found\n");
		st_cmd->keep = 1;
	}
	else
		ft_dprintf(2, "history specification out of range\n");
	return (1);
}


int				error_fc_histo(char *s, int i, int type, t_st_fc *st_fc)
{
	t_st_cmd	*st_cmd;
	int			len;

	st_cmd = get_st_cmd(NULL);
	ft_dprintf(STDERR_FILENO, "%s: fc: ", SHELL_NAME);
	if (type == invalid_option)
		ft_dprintf(STDERR_FILENO, "-%c: invalid option\n", s[i]);
	else if (type == invalid_mix)
	{
		len = ft_strlen_char(st_fc->flag, '.');
		st_fc->flag[len] = s[i];
		ft_putchar('-');
		write(STDERR_FILENO, st_fc->flag, len + 1);
		ft_dprintf(STDERR_FILENO, ": invalid option mix\n");
	}
	else if (type == editor_unspecified)
		ft_dprintf(2, "-e: option requires an argument\n");
	st_cmd->keep = 1;
	return (-1);
}
