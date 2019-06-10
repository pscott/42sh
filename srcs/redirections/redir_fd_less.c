#include "lexer.h"
#include "cmd_parsing.h"
#include <fcntl.h>
#include <sys/stat.h>

static	int		errors_fd_great(char *tk, int err, int fd, int mode)
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

static	int		check_redirect(char *str)
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

static	int		change_token_close(t_token *next)
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

/*
**	Returns 0 on success
**	Else returns error number
*/

int				redir_fd_less(t_token *redir, t_token *prev, int mode)
{
	int				old_fd;
	t_token			*next;
	int				new_fd;
	struct stat		buf;

	if ((old_fd = check_fd_prev(prev)) < 0)
		old_fd = STDIN_FILENO;
	if (old_fd > 9)
		return (errors_fd_great(NULL, 2, old_fd, mode));
	next = redir->next;
	while (next->type == tk_eat)
		next = next->next;
	if (check_redirect(next->content) == 1)
		return (errors_fd_great(next->content, 1, 0, mode));
	else if (check_redirect(next->content) == -1)
		new_fd = change_token_close(next);
	else
		new_fd = ft_atoi(next->content);
	redir->type = tk_eat;
	if (new_fd != -1)
		next->type = tk_eat;
	if (mode == -1)
		return (0);
	if (new_fd > 9 || (new_fd != -1 && fstat(new_fd, &buf) == -1))
		return (errors_fd_great(NULL, 2, new_fd, mode));
	redirect(new_fd, old_fd, mode);
	return (0);
}
