#include "lexer.h"
#include "cmd_parsing.h"

/*
**	Applies the redirection : example : redirect(2, 0) will make fd 2 become
**	STDIN
*/

void				redirect(int old_fd, int new_fd, int save)
{
	if (save)
		save_reset_stdfd(1);
	if (old_fd == -1)
		close(new_fd);
	else if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
		{
			if (old_fd > 2)
				close(old_fd);
		}
		else
			ft_dprintf(2, "42sh: error: dup2 failed\n");
	}
}

/*
**	Checks to see if the previous token is a valid fd token.
**	Returns -1 if it is not.
*/

int					check_fd_prev(t_token *prev)
{
	int	i;

	if (!prev)
		return (-1);
	if (prev->type == tk_word)
	{
		i = 0;
		while (prev->content[i])
		{
			if (!ft_isdigit(prev->content[i]))
				return (-1);
			i++;
		}
		prev->type = tk_eat;
		return (ft_atoi(prev->content));
	}
	else
		return (-1);
}

/*
**	Calls the appropriate function for the current redirection token.
*/

static t_bool		apply_redirections(t_token *redir, t_token *prev, int mode)
{
	if (!redir)
		return (0);
	else if (ft_strncmp(redir->content, ">", 2) == 0)
		return (redir_great(redir, prev, mode));
	else if (ft_strncmp(redir->content, ">&", 3) == 0)
		return (redir_fd_great(redir, prev, mode));
	else if (ft_strncmp(redir->content, ">>", 3) == 0)
		return (redir_dgreat(redir, prev, mode));
	else if (ft_strncmp(redir->content, "<", 2) == 0)
		return (redir_less(redir, prev, mode));
	else if (ft_strncmp(redir->content, "<&", 3) == 0)
		return (redir_fd_less(redir, prev, mode));
	else
		return (0);
	return (1);
}

/*
**	Parses the simple_command for redirections and applies them
**	Mode == 1 means that it's a no_pipe_builtin call
*/

t_bool				parse_redirections(t_token *token_head, int mode)
{
	t_token	*current;
	t_token	*prev;

	current = token_head;
	if (!current)
		return (0);
	prev = NULL;
	while (is_simple_cmd_token(current))
	{
		if (current->type == tk_redirection)
			if (apply_redirections(current, prev, mode) == 0)
				return (0);
		prev = current;
		current = current->next;
	}
	return (1);
}
