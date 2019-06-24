#include "lexer.h"
#include "ast.h"
#include "line_editing.h"
#include "cmd_parsing.h"
#include "history.h"
#include "errors.h"

int				case_bangbang(t_st_cmd *st_cmd, char **str, int *i, int mode)
{
	t_hist_lst	*insert;
	char		*pattern;
	size_t		len;
	size_t		index[2];

	if (!(insert = st_cmd->hist_lst->prev))
	{
		if (mode)
			return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR, NULL));
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

int				case_nb(t_st_cmd *st_cmd, char **str, int *i, int mode)
{
	t_hist_lst	*insert;
	char		*pattern;
	size_t		len;
	size_t		index[2];
	int			nb;

	if ((nb = ft_atoi(&((*str)[*i]))) == 0)
	{
		if (mode)
			return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR, NULL));
		return (1);
	}
	if (nb < 0)
		insert = get_entry_lst(st_cmd->hist_lst, *st_cmd->hist_len + nb + 1);
	else
		insert = get_entry_lst(st_cmd->hist_lst, nb);
	len = ft_strlen_char(insert->txt, '\n');
	if (!(pattern = ft_strndup(insert->txt, len)))
		clean_exit(1, 1);
	index[0] = *i - 1;
	refresh_i(nb, i);
	index[1] = *i;
	substitute_slice(str, index, pattern);
	free(pattern);
	return (0);
}

int				case_word(t_st_cmd *st_cmd, char **str, int *i, int mode)
{
	t_hist_lst	*insert;
	char		*pattern;
	size_t		len;
	size_t		index[2];

	if (!(insert = get_entry_lst_word(st_cmd->hist_lst, &((*str)[*i]))))
	{
		if (mode)
			return (print_errors(ERR_NOT_FOUND, ERR_NOT_FOUND_STR, NULL));
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

int				replace_bang(char **str, int mode)
{
	int			i;
	int			ret;
	t_st_cmd	*st_cmd;

	i = -1;
	st_cmd = get_st_cmd(NULL);
	ret = 0;
	while (str && *str && (*str)[++i])
	{
		if ((*str)[i] == '\'' && !is_quoted_sqt(*str, i))
			go_to_matching_sqt(str, &i);
		if ((*str)[i] == '!' && !is_quoted_bang(*str, i) && (*str)[++i])
		{
			if ((*str)[i] == '!' && (!is_quoted_bang(*str, i)))
				ret = case_bangbang(st_cmd, str, &i, mode);
			else if (ft_isdigit((*str)[i]) || (*str)[i] == '-')
				ret = case_nb(st_cmd, str, &i, mode);
			else if (ft_is_white_space((*str)[i]))
				i++;
			else
				ret = case_word(st_cmd, str, &i, mode);
		}
		ft_dprintf(2, "\n str :{%s}", *str);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
