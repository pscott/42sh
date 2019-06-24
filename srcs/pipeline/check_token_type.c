/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "ast.h"

/*
**	Returns 0 if token is a pipe (or bigger), or an eat token.
**	Returns 1 on quotes, words, monochars, and redirections.
*/

int			is_argv_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type > tk_eat && probe->type < tk_pipe)
		return (1);
	return (0);
}

/*
**	Returns 0 if token is bigger than a pipe.
**	Else returns 1.
*/

int			is_simple_cmd_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type < tk_pipe)
		return (1);
	else
		return (0);
}
