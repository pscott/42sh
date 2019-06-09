/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/08 21:49:48 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

static void	sanitize_pos_values(int *col, int *row)
{
	(*col)--;
	(*row)--;
	if (*col < 0)
		*col = 0;
	if (*row < 0)
		*row = 0;
}

static int	is_good_format(char *pos_str, t_pos *curr_pos)
{
	char	*start;
	char	*col_start;

	if (!(start = ft_strchr(pos_str, 27)))
		return (0);
	curr_pos->row = ft_atoi(start + 2);
	if (!(col_start = ft_strchr(pos_str, ';')))
		return (0);
	curr_pos->col = ft_atoi(col_start + 1);
	return (1);
}

static void	get_pos(char *pos_str, t_pos *curr_pos)
{
	int	len;

	while (!is_good_format(pos_str, curr_pos))
	{
		tputs(GET_POS, 1, put_special_fd);
		if ((len = read(STDIN_FILENO, pos_str, 50)) < 0)
		{
			ft_dprintf(2, "error: failed to read\n");
			pos_str = NULL;
			break ;
		}
		pos_str[len] = 0;
	}
}

void		retrieve_pos(t_pos *curr_pos)
{
	char	pos_str[50];

	if (!g_isatty)
		return ;
	ft_bzero(pos_str, 50);
	get_pos(pos_str, curr_pos);
}

int			move_cursor(int col, int row)
{
	char	buf[50];
	char	*gotostr;
	char	*ap;

	if (!g_isatty)
		return (1);
	sanitize_pos_values(&col, &row);
	ft_bzero(buf, 50);
	ap = buf;
	if (!(gotostr = tgetstr(MOVE_CURSOR, &ap)))
		return (err_tgoto(MOVE_CURSOR));
	if (!(gotostr = tgoto(gotostr, col, row)))
		return (err_tgoto(MOVE_CURSOR));
	tputs(gotostr, 0, put_special_fd);
	return (0);
}
