#include "cmd_parsing.h"

int		errors_fd_great(char *tk, int err, int fd, int mode)
{
	if (mode != -1)
	{
		if (err == 1)
			ft_dprintf(STDERR_FILENO, "42sh: %s: ambiguous redirect\n", tk);
		else if (err == 2)
			ft_dprintf(STDERR_FILENO, "42sh: %d: bad file descriptor\n", fd);
	}
	return (1);
}

int		check_redirect(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		return (-1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int		change_token_close(t_token *next)
{
	char	*new;

	if (!(new = ft_strdup(next->content + 1)))
		clean_exit(1, 1);
	ft_strdel(&next->content);
	next->content = new;
	if (is_full_of_whitespaces(next->content))
		next->type = tk_eat;
	return (-1);
}

int		get_new_fd(t_token *next, int mode)
{
	int	new_fd;

	if (check_redirect(next->content) == 1)
		return (errors_fd_great(next->content, 1, 0, mode));
	else if (check_redirect(next->content) == -1)
		new_fd = change_token_close(next);
	else
		new_fd = ft_atoi(next->content);
	return (new_fd);
}
