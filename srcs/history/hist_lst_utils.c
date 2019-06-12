/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_lst_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschoenh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:38:02 by aschoenh          #+#    #+#             */
/*   Updated: 2019/06/12 15:38:07 by aschoenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "history.h"

t_hist_lst	*create_hist_lst(const char *line, char keep)
{
	t_hist_lst	*res;

	if (!(isatty(TERM_FD)))
		return (NULL);
	if (!(res = (t_hist_lst*)malloc(sizeof(*res))))
		clean_exit(1, 1);
	if (!(res->txt = ft_strdup(line)))
		clean_exit(1, 1);
	if (!(res->cpy = ft_strdup(line)))
		clean_exit(1, 1);
	res->keep = keep;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

void		free_hist_lst(t_hist_lst *hist_lst)
{
	t_hist_lst *tmp;
	t_hist_lst *probe;

	if (!hist_lst)
		return ;
	probe = get_begin_lst(hist_lst);
	while (probe)
	{
		tmp = probe;
		probe = probe->next;
		ft_strdel(&tmp->txt);
		ft_strdel(&tmp->cpy);
		ft_memdel((void*)&tmp);
	}
}

/*
** Debugging function
*/

void		print_hist_lst(t_hist_lst *hist_lst)
{
	t_hist_lst *probe;

	probe = get_begin_lst(hist_lst);
	ft_dprintf(TERM_FD, "--- PRINTING LST --- \n");
	while (probe)
	{
		ft_dprintf(TERM_FD, "PROBE: TXT: {%s}\n", probe->txt);
		probe = probe->next;
	}
}
