#include "input.h"
#include "line_editing.h"

static void	get_next_word(t_st_cmd *st_cmd)
{
	t_st_txt		*st_txt;
	unsigned int	limit;

	st_txt = st_cmd->st_txt;
	limit = st_txt->data_size;
	while (!ft_is_white_space(st_txt->txt[st_txt->tracker])
			&& ft_is_metachar(st_txt->txt[st_txt->tracker])
			&& st_txt->tracker < limit)
		st_txt->tracker++;
	while (!ft_is_white_space(st_txt->txt[st_txt->tracker])
			&& st_txt->tracker < limit)
	{
		if (ft_is_white_space(st_txt->txt[st_txt->tracker])
				|| ft_is_metachar(st_txt->txt[st_txt->tracker]))
			return ;
		st_txt->tracker++;
	}
	while (ft_is_white_space(st_txt->txt[st_txt->tracker])
			&& st_txt->tracker < limit)
		st_txt->tracker++;
}

static void	refresh_tracker_value(t_st_txt *st_txt)
{
	if (st_txt->tracker > 0)
		st_txt->tracker--;
	while (st_txt->tracker > 0
			&& ft_is_white_space(st_txt->txt[st_txt->tracker]))
		st_txt->tracker--;
}

static void	get_prev_word(t_st_cmd *st_cmd)
{
	t_st_txt		*st_txt;

	st_txt = st_cmd->st_txt;
	refresh_tracker_value(st_txt);
	if (ft_is_metachar(st_txt->txt[st_txt->tracker]))
	{
		while (st_txt->tracker > 0
				&& ft_is_metachar(st_txt->txt[st_txt->tracker - 1]))
		{
			if (ft_is_white_space(st_txt->txt[st_txt->tracker - 1]))
				return ;
			st_txt->tracker--;
		}
	}
	else
	{
		while (st_txt->tracker > 0)
		{
			if (ft_is_metachar(st_txt->txt[st_txt->tracker - 1])
					|| ft_is_white_space(st_txt->txt[st_txt->tracker - 1]))
				return ;
			st_txt->tracker--;
		}
	}
}

/*
**	Jumps the number of words provided by the num int.
**	Does not reposition cursor.
*/

int			jump_words(t_st_cmd *st_cmd, int num)
{
	if (num == -2147463648)
		return (0);
	if (num >= 0)
	{
		while (num)
		{
			get_next_word(st_cmd);
			num--;
		}
	}
	else
	{
		while (num)
		{
			get_prev_word(st_cmd);
			num++;
		}
	}
	return (num);
}
