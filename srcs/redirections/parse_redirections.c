/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:05 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:09 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "cmd_parsing.h"

static	void	save_close_fds(int new_fd, int old_fd)
{
	if (old_fd > 2)
		save_close_openfds(old_fd, 1);
	if (new_fd > 2)
		save_close_openfds(new_fd, 1);
}

/*
**	Applies the redirection : example : redirect(2, 0) will make fd 2 become
**	STDIN
*/

void			redirect(int old_fd, int new_fd, int save)
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
				close(old_fd);
		}
		else
		{
			ft_dprintf(2, SHELL_NAME ": error: dup2 failed\n");
			clean_exit(1, 0);
		}
	}
}

/*
**	Checks to see if the previous token is a valid fd token.
**	Returns -1 if it is not.
*/

int				check_fd_prev(t_token *prev)
{
	int				i;

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
**	Returns 0 on success, > 0 on fail.
*/

static int		apply_redirections(t_token *redir,
		t_token *prev, int in_fork)
{
	if (!redir)
		return (0);
	else if (ft_strncmp(redir->content, ">", 2) == 0)
		return (redir_great(redir, prev, in_fork));
	else if (ft_strncmp(redir->content, ">&", 3) == 0)
		return (redir_fd_great(redir, prev, in_fork));
	else if (ft_strncmp(redir->content, ">>", 3) == 0)
		return (redir_dgreat(redir, prev, in_fork));
	else if (ft_strncmp(redir->content, "<", 2) == 0)
		return (redir_less(redir, prev, in_fork));
	else if (ft_strncmp(redir->content, "<&", 3) == 0)
		return (redir_fd_less(redir, prev, in_fork));
	else
		return (1);
	return (0);
}

/*
**	Parses the simple_command for redirections and applies them
**	Mode == 1 means that it's a no_pipe_builtin call
**	Returns 0 on success
**	Returns error number on failure
*/

int				parse_redirections(t_token *token_head, int in_fork)
{
	t_token	*current;
	t_token	*prev;
	int		ret;

	current = token_head;
	if (!current)
		return (0);
	prev = NULL;
	while (is_simple_cmd_token(current))
	{
		if (current->type == tk_redirection)
			if ((ret = apply_redirections(current, prev, in_fork)) > 0)
				return (ret);
		prev = current;
		current = current->next;
	}
	return (0);
}
