/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/05/09 15:59:01 by pscott           ###   ########.fr       */
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

static void	parse_pos(char *pos_str, t_pos *curr_pos)
{
	char			*col_start;

	if (!pos_str)
	{
		curr_pos->row = 0;
		curr_pos->col = 0;
	}
	else
	{
		curr_pos->row = ft_atoi(pos_str + 2);
		col_start = ft_strchr(pos_str + 3, ';');
		curr_pos->col = col_start ? ft_atoi(col_start + 1) : 0;
	}
}

static void	get_pos(char *pos_str)
{
	int	len;

	while (ft_atoi(pos_str + 2) == 0)
	{
		tputs(GET_POS, 1, ft_putchar);
		if (isatty(STDIN_FILENO))
		{
			if ((len = read(STDIN_FILENO, pos_str, 50)) < 0)
			{
				term_putstr_endline("error: failed to read", 2);
				pos_str = NULL;
				break ;
			}
			pos_str[len] = 0;
		}
		else
			break ;
	}
}

void		retrieve_pos(t_pos *curr_pos)
{
	char	pos_str[50];

	ft_bzero(pos_str, 50);
	get_pos(pos_str);
	parse_pos(pos_str, curr_pos);
}

int			move_cursor(int col, int row)
{
	char	buf[50];
	char	*gotostr;
	char	*ap;

	sanitize_pos_values(&col, &row);
	ft_bzero(buf, 50);
	ap = buf;
	if (!(gotostr = tgetstr(MOVE_CURSOR, &ap)))
		return (err_no_str(MOVE_CURSOR));
	if (!(gotostr = tgoto(gotostr, col, row)))
		return (err_tgoto(MOVE_CURSOR));
	tputs(gotostr, 1, ft_putchar);
	return (1);
}
