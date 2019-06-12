/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:06 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:10 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "input.h"

void	clean_heredoc(t_st_cmd *st_cmd, t_st_cmd *start_heredoc)
{
	t_st_cmd *tmp;

	while (st_cmd != start_heredoc)
		st_cmd = st_cmd->prev;
	st_cmd->prev->next = NULL;
	while (st_cmd)
	{
		tmp = st_cmd;
		st_cmd = st_cmd->next;
		free_st_cmd(tmp);
	}
}
