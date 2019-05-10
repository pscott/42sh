#include "ast.h"
#include "lexer.h"

t_bool		redir_fd_great(t_token *redir, t_token *prev)
{
	int		old_fd;
	t_token	*next;
	int		new_fd;

	if ((old_fd = check_fd_prev(prev)) < 0)
		old_fd = 1;//FILENO ??
	next = redir->next;
	while (next->type == TK_EAT) // need functions that does this
		next = next->next;
	if ((new_fd = open(next->content, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
	{
		dprintf(2, "error openening file\n");
		return (0);
	}
	redirect(new_fd, old_fd);
	redir->type = TK_EAT;
	next->type = TK_EAT; // if I dont check is_argv i will segfault on deference
	return (1);
}
