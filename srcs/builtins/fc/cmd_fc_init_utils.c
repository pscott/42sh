#include "ftsh.h"
#include "builtins.h"
#include "auto_completion.h"

int				get_correct_nb(char *to_find, int hist_len)
{
	int			nb;
	int			i;
	char		*corr;

	i = -1;
	while (to_find[++i] == 0)
		;
	if (!(corr = ft_strndup(to_find + i, 5)))
		clean_exit(1, MALLOC_ERR);
	nb = ft_atoi(corr);
	if (nb < 0 && hist_len + nb >= 0)
		nb += hist_len + 1;
	else if (hist_len + nb < 0)
		nb = 1;
	else if (nb == 0 || nb > hist_len)
		nb = hist_len;
	free(corr);
	return (nb);
}

int				check_if_arg_is_digit(char *to_find)
{
	if (ft_isdigit(to_find[0])
		|| (to_find[0] == '-' && ft_strcmp(to_find, "--")
			&& ft_isonly("0123456789", to_find))
		|| (to_find[0] == '+' && ft_isonly("0123456789", to_find)))
		return (1);
	return (0);
}

int				get_last(t_st_cmd *st_cmd, t_st_fc *st_fc)
{
	if (st_fc->last)
	{
		if ((st_fc->i_last = find_index_fc(
					st_cmd, st_fc->flag, st_fc->last)) < 0)
			return (st_fc->i_last);
	}
	else if (ft_strchr(st_fc->flag, 'l'))
		st_fc->i_last = (*st_cmd->hist_len);
	else
		st_fc->i_last = st_fc->i_first;
	return (0);
}

int				get_first_no_indication(t_st_cmd *st_cmd, t_st_fc *st_fc)
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
	return (0);
}

void			swap_fc(t_st_fc *st_fc)
{
	st_fc->i_first ^= st_fc->i_last;
	st_fc->i_last ^= st_fc->i_first;
	st_fc->i_first ^= st_fc->i_last;
	if (!ft_strchr(st_fc->flag, 'r'))
		st_fc->flag[ft_strlen(st_fc->flag)] = 'r';
}
