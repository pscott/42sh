#include "ftsh.h"
#include "builtins.h"
#include "auto_completion.h"

/*
**	Parses FC flags, while preventing bad flag association.
**	Returns (1) if an error occurs.
**	Else, returns (i), the index of the first operand.
*/

static int		fc_parse_flags(t_st_fc *st_fc, char **argv)
{
	int			i;
	int			j;
	int			k;
	int			is_val;

	i = 0;
	while (argv[++i] && argv[i][0] == '-' && ft_strncmp(argv[i], "--", 3))
	{
		j = 0;
		k = -1;
		while (argv[i][++j])
		{
			if (!is_valid_option(argv[i][j]))
				return (error_fc(argv[i], j, invalid_option, st_fc));
			if (((is_val = is_valid_mix(st_fc->flag, argv[i][j]))) == 1)
				st_fc->flag[++k] = argv[i][j];
			else if (is_val == -1)
				return (error_fc(argv[i], j, invalid_mix, st_fc));
		}
	}
	if (!ft_strcmp(argv[i], "--"))
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
		if ((i_editor = (parse_editor_fc(argv, i))) == -1)
			return (-1);
		if (!(st_fc->editor = ft_strtrim(argv[i_editor])))
			clean_exit(1, 1);
		get_first_and_last(st_fc, argv, i_editor + 1);
	}
	else if (st_fc->flag[0] == 's')
	{

		return (parse_case_s_fc(st_fc, argv, i));
	}
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

static int	find_index_fc(t_st_cmd *st_cmd, char *to_find)
{
	int			i;
	int			nb;
	int			len;

	i = 0;
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	if (st_cmd->hist_lst)
	{
		if (ft_isdigit(to_find[0]) || to_find[0] == '-')
		{
			if (to_find[0] == '-')
			{
				i = 0;
				while (to_find[++i] && ft_isdigit(to_find[i]))
					;
				if (to_find[i])
					return (error_fc(to_find, i, invalid_option, NULL));//invalid option -> considere comme une opton
			}
			nb = ft_atoi(to_find);
			if (nb < 0 && (*st_cmd->hist_len) + nb >= 0)
				nb += (*st_cmd->hist_len);
			else if ((*st_cmd->hist_len) + nb < 0)
				nb = 0;
			return (nb);
		}
		i = (*st_cmd->hist_len);//HIST LEN EST PAS UPDATE apres chaque entry
		len = ft_strlen(to_find);
		while (st_cmd->hist_lst->prev && i-- > 0)// a checker 
		{
			if (!ft_strncmp(to_find, st_cmd->hist_lst->txt, len))
				break ;
			st_cmd->hist_lst = st_cmd->hist_lst->prev;
		}
	}
	return (i);
}

/*
**	Get the good values for index_first and index_last in our
**		struct_fc (i.e i_last cannot be superior to hist_len...).
**	Returns 0 on success.
**	Returns 1 if find_index failed.
*/

static int		fc_parse_index(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	if (st_fc->flag[0] == 's')
	{
		if (!st_fc->first)
			st_fc->i_first = (*st_cmd->hist_len) - 1;
		else
			st_fc->i_first = find_index_fc(st_cmd, st_fc->first);// chec -1
	}
	else
	{
		if (st_fc->first)
			st_fc->i_first = find_index_fc(st_cmd, st_fc->first);// check -1
		else
		{
			if (ft_strchr(st_fc->flag, 'l'))
			{
				if ((*st_cmd->hist_len) > 15)
					st_fc->i_first = (*st_cmd->hist_len) - 15;
				else
					st_fc->i_first = 0;
			}
			else
				st_fc->i_last = (*st_cmd->hist_len) - 1;
		}
		if (st_fc->last)
			st_fc->i_last = find_index_fc(st_cmd, st_fc->last); // check -1
		else if (ft_strchr(st_fc->flag, 'l'))
			st_fc->i_last = (*st_cmd->hist_len) - 1;
		else
			st_fc->i_last = st_fc->i_first;
	}
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	return (0);
}

/*
**	Fill the struct_fc with adequate values : 
**		flags, char *first & last, index first & last, pattern substitution,
**		& editor used.
**	Returns 0 on success.
**	Returns 1 on failure.
*/

int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			start_operand;

	i = 5;
	if (!isatty(TERM_FD))
		return (1);
	while (--i > -1)
		(*st_fc).flag[i] = '.';
	if ((start_operand = fc_parse_flags(st_fc, argv)) == -1)
		return (1);
	if ((fc_parse_operands(st_fc, argv, start_operand)) == -1)
		return (1);
	fc_parse_index(st_cmd, st_fc);
	/*
	ft_dprintf(2, "first: %s\nlast: %s\n", st_fc->first, st_fc->last);
	ft_dprintf(2, "i_first: %d\ni_last: %d\n", st_fc->i_first, st_fc->i_last);
	ft_dprintf(2, "old: %s\nnew: %s\n", st_fc->old_ptrn, st_fc->new_ptrn);
	ft_dprintf(2, "editor:%s\n", st_fc->editor);
	*/
	if (st_fc->i_first && st_fc->i_last && !ft_strchr(st_fc->flag, 's')
		&& st_fc->i_first > st_fc->i_last
		&& !ft_strchr(st_fc->flag, 'r'))
	{
		st_fc->i_first ^= st_fc->i_last;
		st_fc->i_last ^= st_fc->i_first;
		st_fc->i_first ^= st_fc->i_last;
	}
	/*
	ft_dprintf(2, "first: %s\nlast: %s\n", st_fc->first, st_fc->last);
	ft_dprintf(2, "i_first: %d\ni_last: %d\n", st_fc->i_first, st_fc->i_last);
	ft_dprintf(2, "old: %s\nnew: %s\n", st_fc->old_ptrn, st_fc->new_ptrn);
	ft_dprintf(2, "editor:%s\n", st_fc->editor);
	*/
	return (0);
}
