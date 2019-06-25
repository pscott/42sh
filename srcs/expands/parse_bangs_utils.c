#include "cmd_parsing.h"

void			refresh_i(int nb, int *i, int ret)
{
	if (ret == 2)
		++(*i);
	while ((nb = nb / 10))
		++(*i);
}

int				is_quoted_char(char *s, int i, char c)
{
	if (s[i] == c)
	{
		if (i > 0)
		{
			if (s[i - 1] == '\\')
				return (1);
		}
	}
	return (0);
}

int				go_to_matching_sqt(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i])
	{
		if ((*str)[*i] == '\'' && !is_quoted_char(*str, *i, '\''))
			break ;
		else
			++(*i);
	}
	return (0);
}

int				go_to_matching_dqt(char **str, int *i)
{
	(*i)++;
	while ((*str)[*i])
	{
		if ((*str)[*i] == '\"' && !is_quoted_char(*str, *i, '\"'))
			break ;
		else
			++(*i);
	}
	return (0);
}

int				get_correct_nb_bang(char *to_find, int hist_len, int *nb)
{
	int			i;
	char		*corr;
	int			ret;

	i = -1;
	while (to_find[++i] == 0)
		;
	if (!(corr = ft_strndup(to_find + i, 5)))
		clean_exit(1, 1);
	*nb = ft_atoi(corr);
	ret = 0;
	if (*nb == 0 || *nb > hist_len || *nb * -1 > hist_len)
		ret = 1;
	else if (*nb < 0 && hist_len + *nb >= 0)
	{
		nb += hist_len + 1;
		ret = 2;
	}
	free(corr);
	return (ret);
}
