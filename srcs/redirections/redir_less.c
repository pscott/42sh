#include "lexer.h"
#include "cmd_parsing.h"
#include "libterm.h"
#include <fcntl.h>

static int	print_fd_error(int fd, int mode)
{
	if (mode != -1)
		ft_dprintf(2, "42sh: %d: bad file descriptor\n", fd);
	return (1);
}

static int	print_file_error(char *filename, int mode)
{
	if (mode != -1)
		ft_dprintf(2, "42sh: %s: No such file or directory\n", filename);
	return (1);
}

/*
**	Returns 0 on success
**	Else returns error number
*/

int			redir_less(t_token *redir, t_token *prev, int mode)
{
	int		old_fd;
	t_token	*next;
	int		new_fd;

	if ((old_fd = check_fd_prev(prev)) < 0)
		old_fd = STDIN_FILENO;
	if (old_fd > 9)
		return (print_fd_error(old_fd, mode));
	next = redir->next;
	while (next->type == tk_eat)
		next = next->next;
	redir->type = tk_eat;
	next->type = tk_eat;
	if ((new_fd = open(next->content, O_RDONLY)) < 0)
		return (print_file_error(next->content, mode));
	redirect(new_fd, old_fd, mode);
	return (0);
}
