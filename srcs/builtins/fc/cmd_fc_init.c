#include "ftsh.h"
#include "builtins.h"
#include "auto_completion.h"

/*
**	Parses FC flags, while preventing bad flag association.
**	Returns (1) if an error occurs.
**	Else, returns (i), the index of the first operand.
*/

static int		fc_parse_flags(t_st_fc *st_fc, char **av)
{
	int			i;
	int			j;
	int			k;
	int			is_val;

	set_ints_to_zero(&i, &k);
	while (k != 2 && av[++i] && av[i][0] == '-' && ft_strncmp(av[i], "--", 3))
	{
		set_ints_to_zero(&j, &k);
		while (av[i][++j])
		{
			if (((k = option(av[i], j)) == 0) && !ft_strnequ(av[i], "-e", 2))
				return (error_fc_histo(av[i], j, invalid_option, st_fc));
			else if (k == 2)
				break ;
			if (((is_val = is_valid_mix(st_fc->flag, av[i][j]))) == 1)
				st_fc->flag[ft_strlen_char(st_fc->flag, '.')] = av[i][j];
			else if (is_val == -1)
				return (error_fc_histo(av[i], j, invalid_mix, st_fc));
		}
	}
	if (!ft_strcmp(av[i], "--"))
		i++;
	return (i);
}

/*
**	Parse operands depending on activated flags.
**	Return (0) on success.
**	Returns (-1) if the editor asked cannot be found in PATH.
*/

static int		fc_parse_operands(t_st_fc *st_fc, char **argv, int i)
{
	int			i_editor;

	if (ft_strchr(st_fc->flag, 'e'))
	{
		if ((i_editor = (parse_editor_fc(argv, i - 1))) == -1)
			return (-1);
		if (ft_strnequ(argv[i_editor], "-e", 2))
			st_fc->editor = ft_strtrim(argv[i_editor] + 2);
		else
			st_fc->editor = ft_strtrim(argv[i_editor]);
		if (!(st_fc->editor))
			clean_exit(1, 1);
		get_first_and_last(st_fc, argv, i_editor + 1);
	}
	else if (st_fc->flag[0] == 's')
		return (parse_case_s_fc(st_fc, argv, i));
	else
		get_first_and_last(st_fc, argv, i);
	return (0);
}

/*
**	Get the index of a char *to_find in the history.
**	Returns (i), the index, on success.
**	Returns -1 on failure (i.e the index is invalid, such as -8945+2,
**		which is considered as an option).
*/

int				find_index_fc(t_st_cmd *st_cmd, char *flag, char *to_find)
{
	int			i;

	i = -1;
	if (st_cmd->hist_lst)
	{
		st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
		if (check_if_arg_is_digit(to_find))
			return (get_correct_nb(to_find, *st_cmd->hist_len));
		else
		{
			i = (*st_cmd->hist_len) + 1;
			while (st_cmd->hist_lst && --i >= 0)
			{
				if (st_cmd->hist_lst->prev)
					st_cmd->hist_lst = st_cmd->hist_lst->prev;
				if (!ft_strncmp(to_find, st_cmd->hist_lst->txt,
						ft_strlen(to_find)))
					break ;
				if (i == 0)
					return (error_fc_index(flag));
			}
		}
	}
	return (i);
}

/*
**	Get the good values for index_first and index_last in our
**		struct_fc.
**	Returns 0 on success.
**	Returns 1 if find_index failed.
*/

static int		fc_parse_index(t_st_cmd *st_cmd, t_st_fc *s)
{
	int			ret;

	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	if (s->flag[0] == 's')
	{
		if (!s->first)
			s->i_first = (*st_cmd->hist_len);
		else if ((s->i_first = find_index_fc(st_cmd, s->flag,
					s->first)) < 0)
			return (s->i_first);
	}
	else
	{
		if (s->first)
		{
			if ((s->i_first = find_index_fc(st_cmd, s->flag, s->first)) < 0)
				return (s->i_first);
		}
		else
			get_first_no_indication(st_cmd, s);
		if ((ret = get_last(st_cmd, s)) < 0)
			return (s->i_last);
	}
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	return (0);
}

/*
**	Fill the struct_fc with adequate values :
**		flags, char *first & last, index first & last, pattern substitution
**		& editor used.
**	Returns 0 on success.
**	Returns 1 on failure.
*/

int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			start_operand;

	i = 5;
	while (--i > -1)
		(*st_fc).flag[i] = '.';
	if ((start_operand = fc_parse_flags(st_fc, argv)) == -1)
		return (1);
	else if (start_operand == -2)
		return (2);
	if ((fc_parse_operands(st_fc, argv, start_operand)) == -1)
		return (1);
	if (*st_cmd->hist_len == 0)
	{
		error_fc_index(st_fc->flag);
		return (1);
	}
	if ((fc_parse_index(st_cmd, st_fc)) == -1)
		return (1);
	if (st_fc->i_first && st_fc->i_last && !ft_strchr(st_fc->flag, 's')
			&& st_fc->i_first > st_fc->i_last)
		swap_fc(st_fc);
	if (st_fc->i_last > *st_cmd->hist_len)
		st_fc->i_last = *st_cmd->hist_len;
	return (0);
}
