/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_select_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 11:21:14 by penzo             #+#    #+#             */
/*   Updated: 2019/06/24 11:21:18 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftsh.h"
#include "line_editing.h"

static size_t	set_highest(size_t highest, size_t start, size_t end)
{
	if (end < start)
		highest = highest > start ? start : highest;
	else
		highest = end;
	return (highest);
}

static void		delete_selection(t_st_cmd *st_cmd, t_vars *vars)
{
	t_st_txt	*txt;
	size_t		select_size;
	size_t		lowest;
	size_t		highest;

	txt = st_cmd->st_txt;
	lowest = vars->select_start < vars->select_end
		? vars->select_start : vars->select_end;
	highest = set_highest(lowest + ft_strlen(&txt->txt[lowest]),
			vars->select_start, vars->select_end);
	select_size = highest - lowest + 1;
	txt->txt = ft_realloc(txt->txt, txt->data_size,
			&txt->malloc_size, select_size);
	shift_chars_left(&txt->txt[lowest], select_size);
	if (vars->select_end > vars->select_start)
	{
		if (txt->tracker > highest - lowest)
			txt->tracker -= (highest - lowest);
		else
			txt->tracker = 0;
	}
	txt->data_size = txt->data_size > select_size
		? txt->data_size - select_size : 0;
	txt->data_size = txt->data_size > txt->tracker
		? txt->data_size : txt->tracker;
}

static void		copy_selection(t_st_cmd *st_cmd, t_vars *vars)
{
	size_t	highest;
	size_t	lowest;
	size_t	size;
	char	*txt;

	ft_strdel(&vars->copy);
	txt = st_cmd->st_txt->txt;
	lowest = vars->select_start < vars->select_end
		? vars->select_start : vars->select_end;
	highest = vars->select_start < vars->select_end
		? vars->select_end : vars->select_start;
	size = highest - lowest + 1;
	if (!(vars->copy = ft_strndup(&txt[lowest], size)))
		clean_exit(1, 1);
}

static int		check_for_copy(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	if (ft_strequ(buf, ALT_X))
	{
		if (!vars->select_mode)
			return (1);
		copy_selection(st_cmd, vars);
		delete_selection(st_cmd, vars);
		vars->select_mode = 0;
		return (1);
	}
	else if (ft_strequ(buf, ALT_C))
	{
		if (!vars->select_mode)
			return (1);
		copy_selection(st_cmd, vars);
		vars->select_mode = 0;
		return (1);
	}
	return (0);
}

/*
**	Checks for copy, paste and cut characters.
*/

int				check_for_select_mode(t_st_cmd *st_cmd, char *buf, t_vars *vars)
{
	size_t	tmp;
	size_t	lowest;

	lowest = vars->select_start < vars->select_end
		? vars->select_start : vars->select_end;
	if (ft_strequ(buf, F1_KEY) || check_for_copy(st_cmd, buf, vars))
	{
		if (ft_strequ(buf, F1_KEY))
			vars->select_mode = !vars->select_mode;
		if (vars->select_mode == 0)
		{
			tmp = st_cmd->st_txt->tracker;
			reposition_cursor(st_cmd, lowest);
			execute_str(CLEAR_BELOW);
			write_st_cmd(st_cmd);
			reposition_cursor(st_cmd, tmp);
		}
		vars->select_start = st_cmd->st_txt->tracker;
		vars->select_end = st_cmd->st_txt->tracker;
		return (1);
	}
	else if (check_select_paste(st_cmd, buf, vars))
		return (1);
	else
		return (0);
}
