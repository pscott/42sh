#include "lexer.h"
#include "ast.h"
#include "line_editing.h"
#include "cmd_parsing.h"
#include "history.h"
#include "errors.h"
#include "builtins.h"

int				case_bangbang(t_st_cmd *st_cmd, char **str, int *i, int mode)
{
	t_hist_lst	*insert;
	char		*pattern;
	size_t		len;
	size_t		index[2];

	if (!(insert = st_cmd->hist_lst->prev))
	{
		if (mode)
			return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR,
						&((*str)[(*i) - 1])));
		return (1);
	}
	if (st_cmd->cr == 1 && insert->prev)
		insert = insert->prev;
	len = ft_strlen_char(insert->txt, '\n');
	if (!(pattern = ft_strndup(insert->txt, len)))
		clean_exit(1, 1);
	index[0] = *i - 1;
	index[1] = *i;
	substitute_slice(str, index, pattern);
	free(pattern);
	return (0);
}

static int		get_correct_nb_bang(char *to_find, int hist_len, int *nb)
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

int				case_nb(t_st_cmd *st_cmd, char **str, int *i, int mode)
{
	t_hist_lst	*insert;
	char		*pattern;
	int			ret;
	size_t		index[2];
	int			nb;

	ret = get_correct_nb_bang(&((*str)[*i]), *st_cmd->hist_len, &nb);
	if (ret == 1)
	{
		if (mode)
			return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR,
						&((*str)[(*i) - 1])));
		return (1);
	}
	if (nb < 0)
		insert = get_entry_lst(st_cmd->hist_lst, *st_cmd->hist_len + nb + 1);
	else
		insert = get_entry_lst(st_cmd->hist_lst, nb);
	if (!(pattern = ft_strndup(insert->txt, ft_strlen_char(insert->txt, '\n'))))
		clean_exit(1, 1);
	index[0] = *i - 1;
	refresh_i(nb, i, ret);
	index[1] = *i;
	substitute_slice(str, index, pattern);
	free(pattern);
	return (0);
}

static int		is_quoted(char *str, int i)
{
	int			k;
	int			quote;

	k = 0;
	quote = -1;
	while (k < i && str[k])
	{
		if (str[k] == '\"')
			quote *= -1;
		k++;
	}
	return (quote);
}

int				case_word(t_st_cmd *st_cmd, char **str, int *i, int mode)
{
	t_hist_lst	*insert;
	char		*pattern;
	size_t		len;
	size_t		index[2];

	if ((*i) > 0 && (*str)[(*i)] == '\"' && is_quoted(*str, *i) == 1)
	{
		(*i)++;
		return (0);
	}
	if (!(insert = get_entry_lst_word(st_cmd->hist_lst, &((*str)[*i]))))
	{
		if (mode)
			return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR,
						&((*str)[(*i) - 1])));
		return (1);
	}
	len = ft_strlen_chars(&((*str)[*i]), " \n\t\r;<>&|");
	if (!(pattern = ft_strndup(insert->txt, ft_strlen_char(insert->txt, '\n'))))
		clean_exit(1, 1);
	index[0] = *i - 1;
	*i = *i + len - 1;
	index[1] = *i;
	substitute_slice(str, index, pattern);
	free(pattern);
	return (0);
}

int				int_vars_bang(t_st_cmd *st_cmd, int *i, int *ret)
{
	*i = -1;
	st_cmd = get_st_cmd(NULL);
	*ret = 0;
	if (st_cmd->is_cr_sqt == 1)
		return (1);
	return (0);
}

int				bang_max(int *count)
{
	write(2, "Too many history expansions.\n", 29);
	count = 0;
	return (1);
}

int				perform_expands(char **str, int *i, int mode, int *count)
{
	int			ret;
	t_st_cmd	*st_cmd;

	ret = 0;
	st_cmd = get_st_cmd(NULL);
	if ((*str)[*i] == '!' && (!is_quoted_char(*str, *i, '!')) && ++(*count))
		ret = case_bangbang(st_cmd, str, i, mode);
	else if ((ft_isdigit((*str)[*i]) || (*str)[*i] == '-') && ++(*count))
		ret = case_nb(st_cmd, str, i, mode);
	else if (ft_is_white_space((*str)[*i]) || (*str)[*i] == '=')
		;
	else
	{
		(*count)++;
		ret = case_word(st_cmd, str, i, mode);
	}
	return (ret);

}

int				replace_bang(char **str, int mode)
{
	int			i;
	int			ret;
	t_st_cmd	*st_cmd;
	static int	count = 0;

	st_cmd = NULL;
	if (int_vars_bang(st_cmd, &i, &ret))
		return (0);
	while (str && *str && (*str)[++i])
	{
		if ((*str)[i] == '\'' && !is_quoted_char(*str, i, '\''))
			go_to_matching_sqt(str, &i);
		else if ((*str)[i] == '\"' && !is_quoted_char(*str, i, '\"'))
			go_to_matching_dqt(str, &i);
		if ((*str)[i] == '!' && !is_quoted_char(*str, i, '!') && (*str)[i + 1])
		{
			if (count > BANG_MAX)
				return (bang_max(&count));
			i++;
			ret = perform_expands(str, &i, mode, &count);
		}
		if (ret != 0)
			return (ret);
	}
	return (0);
}
