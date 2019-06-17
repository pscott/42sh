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
		k = 0;
		while (argv[i][++j])
		{
			if ((k = is_valid_option(argv[i], j)) == 0 && !ft_strnequ(argv[i], "-e", 2))
				return (error_fc_histo(argv[i], j, invalid_option, st_fc));//x=2
			else if (k == 2)
				break ;
			if (((is_val = is_valid_mix(st_fc->flag, argv[i][j]))) == 1)
				st_fc->flag[ft_strlen_char(st_fc->flag, '.')] = argv[i][j];
			else if (is_val == -1)
				return (error_fc_histo(argv[i], j, invalid_mix, st_fc));
		}
		if (k == 2)
			break;
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

static int	find_index_fc(t_st_cmd *st_cmd, char *flag, char *to_find)
{
	int			i;
	int			nb;
	int			len;

	i = 0;
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	if (st_cmd->hist_lst->prev)
		st_cmd->hist_lst = st_cmd->hist_lst->prev;
	if (st_cmd->hist_lst)
	{
		if (ft_isdigit(to_find[0])
			|| (to_find[0] == '-' && ft_strcmp(to_find, "--")
				&& ft_isonly("0123456789", to_find))
			|| (to_find[0] == '+' && ft_isonly("0123456789", to_find)))
		{
			nb = ft_atoi(to_find);
			if (nb < 0 && (*st_cmd->hist_len) + nb >= 0)
				nb += (*st_cmd->hist_len);
			else if ((*st_cmd->hist_len) + nb < 0)
				nb = 1;
			else if (nb == 0)
				nb = *st_cmd->hist_len;
			return (nb);
		}
		i = (*st_cmd->hist_len);
		len = ft_strlen(to_find);
		while (st_cmd->hist_lst && i > 0)// a checker 
		{
			i--;
			if (!ft_strncmp(to_find, st_cmd->hist_lst->txt, len))
				break ;
			if (st_cmd->hist_lst->prev)
				st_cmd->hist_lst = st_cmd->hist_lst->prev;
			if (i == 0)
				return (error_fc_index(flag));//put dans l'histo si l en tout cas
			// ne rentre pas dedans en cas de invalid first. doit return 1
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

static int		fc_parse_index(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	if (st_fc->flag[0] == 's')
	{
		if (!st_fc->first)
			st_fc->i_first = (*st_cmd->hist_len);
		else
		{
			if ((st_fc->i_first = find_index_fc(st_cmd, st_fc->flag, st_fc->first)) < 0)// check -1
				return (st_fc->i_first);
		}
	}
	else
	{
		if (st_fc->first)
		{
			if ((st_fc->i_first = find_index_fc(st_cmd, st_fc->flag, st_fc->first)) < 0)// check -1
				return (st_fc->i_first);
		
		}
		else
		{
			if (ft_strchr(st_fc->flag, 'l'))
			{
				if ((*st_cmd->hist_len) > 15)
					st_fc->i_first = (*st_cmd->hist_len) - 15;
				else
					st_fc->i_first = 1;
			}
			else
				st_fc->i_first = (*st_cmd->hist_len);
		}
		if (st_fc->last)
		{
			if ((st_fc->i_last = find_index_fc(st_cmd, st_fc->flag, st_fc->last)) < 0)// check -1
				return (st_fc->i_last);
		}
		else if (ft_strchr(st_fc->flag, 'l'))
			st_fc->i_last = (*st_cmd->hist_len);
		else
			st_fc->i_last = st_fc->i_first;
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

/*	
	ft_dprintf(2, "-------------------------\n");
	ft_dprintf(2, "first: %s\nlast: %s\n", st_fc->first, st_fc->last);
	ft_dprintf(2, "i_first: %d\ni_last: %d\n\n\n", st_fc->i_first, st_fc->i_last);
	


	
	ft_dprintf(2, "hist_len: %d\n", *st_cmd->hist_len);
	
	ft_dprintf(2, "-------------------------\n");
*/	
/*	
	ft_dprintf(2, "old: %s\nnew: %s\n", st_fc->old_pattern, st_fc->new_pattern);
	ft_dprintf(2, "editor:%s\n", st_fc->editor);
	
//	ft_dprintf(2, "\ni_first: %d\ni_last: %d\n", st_fc->i_first, st_fc->i_last);
//	ft_dprintf(2, "start_ope: %d\n", start_operand);

*/

	if (st_fc->i_first && st_fc->i_last && !ft_strchr(st_fc->flag, 's')
		&& st_fc->i_first > st_fc->i_last
		&& !ft_strchr(st_fc->flag, 'r'))
	{
		st_fc->i_first ^= st_fc->i_last;
		st_fc->i_last ^= st_fc->i_first;
		st_fc->i_first ^= st_fc->i_last;
	}
	if (st_fc->i_last > *st_cmd->hist_len)
		st_fc->i_last = *st_cmd->hist_len ;
	

	
	/*	
	ft_dprintf(2, "-------------------------\n");
	ft_dprintf(2, "first: %s\nlast: %s\n", st_fc->first, st_fc->last);
	ft_dprintf(2, "i_first: %d\ni_last: %d\n", st_fc->i_first, st_fc->i_last);
	ft_dprintf(2, "old: %s\nnew: %s\n", st_fc->old_pattern, st_fc->new_pattern);
	ft_dprintf(2, "editor:%s\n", st_fc->editor);
	*/
	return (0);
}
