/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_escape_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:02 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "lexer.h"
#include "input.h"

int		adjust_escaped(char c, int escaped)
{
	if (c == '\\')
		escaped = (escaped) ? 0 : 1;
	else
		escaped = 0;
	return (escaped);
}

t_token	*trim_escaped_newline(void)
{
	t_st_cmd *st_cmd;

	st_cmd = get_st_cmd(NULL);
	st_cmd = get_last_st_cmd(st_cmd);
	st_cmd->st_txt->data_size -= 2;
	ft_bzero(&st_cmd->st_txt->txt[st_cmd->st_txt->data_size], 2);
	return (NULL);
}

t_token	*get_eat_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (ft_is_white_space((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, tk_eat)))
		clean_exit(1, 1);
	*cmdline = *cmdline + i;
	return (token);
}
