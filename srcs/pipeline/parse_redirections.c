#include "ast.h"
#include "lexer.h"

/*
**	Applies the redirection : example : redirect(2, 0) will make fd 2 become
**	STDIN
*/

void	redirect(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
			close(old_fd); //check close return value ?
		else
			dprintf(2, "error with dup2: old_fd: %d, new_fd: %d\n", old_fd, new_fd);
	}
}

/*
**	Checks to see if the previous token is a valid fd token.
**	Returns -1 if it is not.
*/

int		check_fd_prev(t_token *prev) //should rename 
{
	int	i;

	if (!prev)
		return (-1);
	if (prev->type == TK_WORD)
	{
		i = 0;
		while (prev->content[i])
		{
			if (!ft_isdigit(prev->content[i]))
				return (-1);
			i++;
		}
		prev->type = TK_EAT;
		return (ft_atoi(prev->content));
	}
	else
		return (-1);
}

/*
**	Calls the appropriate function for the current redirection token.
*/

t_bool	apply_redirections(t_token *redir, t_token *prev) //static ?//use redir_table ?
{
	if (!redir)
		return (0);
	else if (ft_strncmp(redir->content, ">", 2) == 0) // only >
		redir_great(redir, prev);
	else if (ft_strncmp(redir->content, "&>", 3) == 0)
		redir_fd_great(redir, prev);
	else if (ft_strncmp(redir->content, ">>", 3) == 0)
		redir_dgreat(redir, prev);
	else if (ft_strncmp(redir->content, "<", 2) == 0)
		return (redir_less(redir, prev));
	else if (ft_strncmp(redir->content, "<<", 3) == 0) //TODO
		redir_dless(redir, prev);
	else
		return (0);
	return (1);
}

/*
**	Parses the simple_command for redirections and applies them
*/

t_bool	parse_redirections(t_token *token_head)
{
	t_token	*current;
	t_token	*prev;

	current = token_head;
	if (!current)
		return (0);
	//if (current->type == TK_REDIRECTION) //set prev to NULL to avoid repeatition
	//	if (apply_redirections(current, NULL) == 0)
	//		return (0);
	//prev = current;
	//current = current->next;
	prev = NULL;
	while (is_simple_cmd_token(current))
	{
		if (current->type == TK_REDIRECTION)
			if (apply_redirections(current, prev) == 0)
				return (0);
		prev = current;
		current = current->next;
	}
	return (execute_tokens(token_head));
}
