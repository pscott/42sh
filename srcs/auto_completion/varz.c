#include "auto_completion.h"

static int		check_vars(char **path, t_auto_comp **match,
		const char *to_find)
{
	char			*filename;
	char			*key;
	int				i;

	filename = NULL;
	i = 0;
	while (path[i])
	{
		if (!(key = ft_strndup(path[i], ft_strlen_char(path[i], '='))))
			clean_exit(1, 1);
		if (ft_strnequ(key, to_find, ft_strlen(to_find)))
		{
			create_match_link(match, key);
		}
		ft_strdel(&key);
		i++;
	}
	return (0);
}

static int		get_matching_varz(t_auto_comp **match,
		const char *to_find_real)
{
	t_vars			*vars;

	vars = get_vars(NULL);
	*match = NULL;
	if (vars->shell_vars)
		check_vars(vars->shell_vars, match, to_find_real);
	if (!(*match))
		return (0);
	return (0);
}

static void			get_space_ret(char **ret, const char *str, const char *next, int len)
{
	int				space;
	char			*tmp_1;

	if (len > 1)
		return ;
	space = 0;
	tmp_1 = NULL;
	if (!next[ft_strlen(str)] || ft_is_white_space(next[ft_strlen(next) - 1]))
		space = 1;
	if (space == 0)
		return ;
	if (space == 1)
	{
		if (!(tmp_1 = ft_strjoin(*ret, " ")))
			clean_exit(1, 1);
	}
	ft_strdel(ret);
	*ret = tmp_1;
}

static void			get_ret(char **ret_str, int mode)
{
	char			*tmp;
	char			prefix[4];
	int				i;

	i = 0;
	while (i < 3)
		prefix[i++] = 0;
	prefix[0] = '$';
	if (mode == 2)
		prefix[1] = '{';
	if (!(tmp = ft_strjoin(prefix, *ret_str)))
		clean_exit(1, 1);
	ft_strdel(ret_str);
	if (!(*ret_str = ft_strdup(tmp)))
		clean_exit(1, 1);
	ft_strdel(&tmp);
}

char				*varz(const char *str, const char *next)
{
	char			*to_find;
	char			*ret_str;
	t_auto_comp		*match;
	int				i;
	int				len;

	i = 0;
	len = 0;
	while (str && ft_is_white_space(str[i]))
		i++;
	i++;
	if (str && str[i] == '{')
		i++;
	if (!(to_find = ft_strdup(str + i)))
		clean_exit(1, 1);
	get_matching_varz(&match, to_find);
	ret_str = NULL;
	if (match)
	{
		len = len_lst(match);
		ret_str = get_ret_or_display_matches(match, to_find,
				ft_strlen(to_find), i - 1);
	}
	if (!ret_str)
	{
		if (!(ret_str = ft_strdup(str)))
			clean_exit(1, 1);
		ft_strdel(&to_find);
		return (ret_str);
	}
	ft_strdel(&to_find);
	get_ret(&ret_str, i);
	get_space_ret(&ret_str, str, next, len);
	return (ret_str);
}
