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
				return (error_fc(argv[i], j, invalid_option, st_fc));//return error directement
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

int				parse_case_s_fc(t_st_fc *st_fc, char **argv, int i)
{
	int			len;

	ft_dprintf(2, "%s %d\n\n", argv[i], i);
	if (ft_strchr(argv[i], '='))
	{
		len = ft_strlen_char(argv[i], '=');
		if (!(st_fc->old_ptrn = ft_strndup(argv[i], len)))
			clean_exit(1, 1);
		if (!(st_fc->new_ptrn = ft_strdup(argv[i] + len + 1)))
			clean_exit(1, 1);
		if (argv[i + 1])
		{
			if (!(st_fc->first = ft_strdup(argv[i + 1])))
				clean_exit(1, 1);
		}
	}
	else
		if (!(st_fc->first = ft_strdup(argv[i])))
			clean_exit(1, 1);
	return (0);
}

int				get_first_and_last(t_st_fc *st_fc, char **argv, int i)
{
	if (!argv[i])
		return (1);
	if (!(st_fc->first))
	{
		if (!(st_fc->first = ft_strdup(argv[i])))
			clean_exit(1, 1);
		i++;
	}
	if (argv[i] && !(st_fc->last) && (st_fc->first))
	{
		if (!(st_fc->last = ft_strdup(argv[i])))
			clean_exit(1, 1);
	}
	return (0);
}


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

int				init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv)
{
	int			i;
	int			start_operand;

	i = 5;
	(void)st_cmd;
	while (--i > -1)
		(*st_fc).flag[i] = '.';
	if ((start_operand = fc_parse_flags(st_fc, argv)) == -1)
		return (1);
	ft_dprintf(2, "{{%d}}", start_operand);
	if ((fc_parse_operands(st_fc, argv, start_operand)) == -1)
		return (1);
	ft_dprintf(2, "%s\n%s\n", st_fc->first, st_fc->last);
	ft_dprintf(2, "%s\n%s\n", st_fc->old_ptrn, st_fc->new_ptrn);
	ft_dprintf(2, "%s\n", st_fc->editor);

	return (0);
}
