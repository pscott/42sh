/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:16 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:19 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_parsing.h"

int		errors_fd_great(char *tk, int err, int fd, int mode)
{
	if (mode != -1)
	{
		if (err == 1)
			ft_dprintf(STDERR_FILENO, SHELL_NAME ": %s: ambiguous redirect\n",
				tk);
		else if (err == 2)
			ft_dprintf(STDERR_FILENO, SHELL_NAME ": %d: bad file descriptor\n",
				fd);
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

/*
**	Returns 0 on success, 1 on failure.
**	Takes the address of new_fd and sets it to the correct new_fd.
**	Undefined value for new_fd if there is an error.
*/

int		get_new_fd(t_token *next, int mode, int *new_fd)
{
	if (check_redirect(next->content) == 1)
	{
		errors_fd_great(next->content, 1, 0, mode);
		return (1);
	}
	else if (check_redirect(next->content) == -1)
		*new_fd = change_token_close(next);
	else
		*new_fd = ft_atoi(next->content);
	return (0);
}
