#include "lexer.h"
#include "cmd_parsing.h"
#include <fcntl.h>
#include <sys/stat.h>

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

	if ((old_fd = check_fd_prev(prev)) < 0)
		old_fd = STDOUT_FILENO;
	if (old_fd > 9)
		return (errors_fd_great(NULL, 2, old_fd, mode));
	next = redir->next;
	while (next->type == tk_eat)
		next = next->next;
	if ((new_fd = get_new_fd(next, mode)) < 0)
		return (1);
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
