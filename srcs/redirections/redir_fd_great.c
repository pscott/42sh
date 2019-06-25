#include "lexer.h"
#include "cmd_parsing.h"
#include <fcntl.h>
#include <sys/stat.h>

static int		get_new_fd_great(t_token *next, int mode, int *new_fd,
		int *left)
{
	if (check_redirect(next->content) == 1 && mode != -1)
	{
		if ((*new_fd = open(next->content, O_WRONLY | O_CREAT | O_TRUNC,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (open_error(next->content, mode));
		*left += 1;
	}
	else if (check_redirect(next->content) == -1)
		*new_fd = change_token_close(next);
	else
		*new_fd = ft_atoi(next->content);
	return (0);
}

static void		great_redirect(int old_fd, int new_fd, int save, int left)
{
	if (save == -1)
		return ;
	if (save)
		save_reset_stdfd(1);
	if (old_fd == -1)
		close(new_fd);
	else if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
		{
			if (save)
				save_close_fds(new_fd, old_fd);
			if (old_fd > 2)
			{
				if (left == 2)
					great_redirect(old_fd, 2, save, 0);
				close(old_fd);
			}
		}
		else
			ft_dprintf(2, SHELL_NAME ": error: dup2 failed\n");
	}
}

static void		double_redir(int *left, int *old_fd)
{
	*left = 1;
	*old_fd = STDOUT_FILENO;
}

/*
**	Returns 0 on success
**	Else returns error number
*/

int				redir_fd_great(t_token *redir, t_token *prev, int mode)
{
	int				old_fd;
	t_token			*next;
	int				new_fd;
	struct stat		buf;
	int				left;

	left = 0;
	if ((old_fd = check_fd_prev(prev)) < 0)
		double_redir(&left, &old_fd);
	if (old_fd > 9)
		return (errors_fd_great(NULL, 2, old_fd, mode));
	next = redir->next;
	while (next->type == tk_eat)
		next = next->next;
	if (get_new_fd_great(next, mode, &new_fd, &left))
		return (1);
	redir->type = tk_eat;
	if (new_fd != -1)
		next->type = tk_eat;
	if (mode == -1)
		return (0);
	if (new_fd > 9 || (new_fd != -1 && fstat(new_fd, &buf) == -1))
		return (errors_fd_great(NULL, 2, new_fd, mode));
	great_redirect(new_fd, old_fd, mode, left);
	return (0);
}
