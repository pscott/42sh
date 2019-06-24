/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*copy_tokens(t_token *token_head)
{
	t_token *probe;
	t_token	*cpy;
	t_token	*last_token;
	t_token	*new_token;

	if (!(probe = token_head))
		return (NULL);
	cpy = create_token(probe->content, probe->size, probe->type);
	probe = probe->next;
	last_token = cpy;
	while (probe)
	{
		new_token = create_token(probe->content, probe->size, probe->type);
		last_token->next = new_token;
		last_token = new_token;
		probe = probe->next;
	}
	return (cpy);
}
