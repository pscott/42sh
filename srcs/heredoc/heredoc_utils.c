/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:17 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:21 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "heredoc.h"

static char	*remove_quot(char *str)
{
	char			*new;
	size_t			str_len;

	str_len = ft_strlen(str);
	if (!(new = ft_strnew(str_len - 2)))
		clean_exit(1, 1);
	ft_strncpy(new, &str[1], str_len - 2);
	return (new);
}

static char	*strjoin_free(char *str_join, char *str_add)
{
	char	*tmp_str;

	if (!(tmp_str = ft_strjoin(str_join, str_add)))
		clean_exit(1, 1);
	ft_strdel(&str_join);
	return (tmp_str);
}

static char	*eof_init(t_token *token)
{
	char	*eof;
	char	*tmp_str;

	eof = NULL;
	if (token->type == tk_word || token->type == tk_monoc)
	{
		if (!(eof = ft_strdup(token->content)))
			clean_exit(1, 1);
	}
	else if (token->type == tk_sq_str || token->type == tk_dq_str)
	{
		if (!(tmp_str = remove_quot(token->content)))
			clean_exit(1, 1);
		if (!(eof = ft_strdup(tmp_str)))
			clean_exit(1, 1);
		ft_strdel(&tmp_str);
	}
	return (eof);
}

/*
** eof_join
** join 2 token->content to the string 'eof'
** and return the concatenated string
*/

char		*eof_join(char *eof, t_token *token)
{
	char	*tmp_str;

	if (!eof)
		eof = eof_init(token);
	else
	{
		if (token->type == tk_word || token->type == tk_monoc)
			eof = strjoin_free(eof, token->content);
		else if (token->type == tk_sq_str || token->type == tk_dq_str)
		{
			if (!(tmp_str = remove_quot(token->content)))
				clean_exit(1, 1);
			eof = strjoin_free(eof, tmp_str);
			ft_strdel(&tmp_str);
		}
	}
	return (eof);
}
