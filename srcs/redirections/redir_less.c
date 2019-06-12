/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:05 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:09 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "cmd_parsing.h"
#include "libterm.h"
#include <fcntl.h>

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
		return (bad_fd_error(old_fd, mode));
	next = redir->next;
	while (next->type == tk_eat)
		next = next->next;
	redir->type = tk_eat;
	next->type = tk_eat;
	if (mode == -1)
		return (0);
	if ((new_fd = open(next->content, O_RDONLY)) < 0)
		return (no_file_error(next->content, mode));
	redirect(new_fd, old_fd, mode);
	return (0);
}
