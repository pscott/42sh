/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/08 19:54:24 by pscott           ###   ########.fr       */
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

static int	fill_pos(char *pos_str, t_pos *curr_pos)
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

int			is_valid_pos_format(char pos_str[POS_BUF_SIZE + 1])
{
	char	*start;
	char	*col_start;

	if (!(start = ft_strchr(pos_str, '\x1b')))
		return (0);
	if ((ft_strncmp(start, "\x1b\x5b", 2)))
		return (0);
	start += 2;
	if (!(col_start = ft_strchr(pos_str, ';')))
		return (0);
	while (start < col_start)
	{
		if (!ft_isdigit(*start))
			return (0);
		start++;
	}
	if (!*start || start != col_start)
		return (0);
	col_start++;
	while (*col_start)
	{
		if (!ft_isdigit(*col_start))
			return (0);
		if (*(col_start + 1) == 'R')
			return (1);
		col_start++;
	}
	return (0);
}

static void	get_pos(char *pos_str)
{
	int	len;

	
	while (!is_valid_pos_format(pos_str))
	{
		tputs(GET_POS, 1, put_special_fd);
		if ((len = read(STDIN_FILENO, pos_str, POS_BUF_SIZE)) < 0)
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
	char	pos_str[POS_BUF_SIZE + 1];

	if (isatty(TERM_FD) == 0)
		return ;
	ft_bzero(pos_str, POS_BUF_SIZE);
	get_pos(pos_str);
	fill_pos(pos_str, curr_pos);
}

int			move_cursor(int col, int row)
{
	char	buf[50];
	char	*gotostr;
	char	*ap;

	if (isatty(TERM_FD) == 0)
		return (0);
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
